#include "space_station.hpp"

#include <algorithm>

#include "pd_helpers.hpp"
#include "static_random_generator.hpp"

bool SpaceStation::loaded = false;
std::vector<AsteroidType> SpaceStation::asteroid_types_;
LCDBitmapTable* SpaceStation::station_bitmap_table_ = nullptr;

void SpaceStation::Generate(const StationArea& station_area) {
  playdate_->system->logToConsole("#SpaceStation::Generate");

  StaticRandomGenerator::get().SetSeed(station_area.seed);
  createAsteroids(station_area);

  running_time_ = 0.0f;
}

void SpaceStation::Update(float dt) {
  running_time_ += dt;

  std::for_each(asteroids_.begin(), asteroids_.end(),
                [dt](auto& a) { a.Update(dt); });
}

void SpaceStation::Draw(const Camera& camera) {
  LCDBitmap* bitmap = SelectFrameLooped(
      playdate_, station_bitmap_table_, kSpaceStationAnimationLength,
      kSpaceStationAnimationNumFrames, running_time_);

  DrawBitmapCentered(playdate_, bitmap, camera.ConvertToCameraSpace(position_));

  if (kDrawDebugStation) {
    drawDebug(camera.ConvertToCameraSpace(position_));
  }

  std::for_each(asteroids_.begin(), asteroids_.end(),
                [&](auto& a) { a.Draw(camera); });
}

void SpaceStation::drawDebug(const Point2d& position) {
  playdate_->graphics->drawEllipse((int)(position.x - kSpaceStationRadius),
                                   (int)(position.y - kSpaceStationRadius),
                                   (int)(kSpaceStationRadius * 2.0f),
                                   (int)(kSpaceStationRadius * 2.0f), 1, 0, 0,
                                   kColorWhite);
}

void SpaceStation::load(PlaydateAPI* playdate) {
  const char* error = nullptr;

  asteroid_types_ = GetAsteroidTypes();
  for (auto& asteroid_type : asteroid_types_) {
    asteroid_type.bitmaps.resize(asteroid_type.models.size());
    for (int i = 0; i < (int)asteroid_type.models.size(); ++i) {
      asteroid_type.bitmaps[i] =
          playdate->graphics->loadBitmap(asteroid_type.models[i], &error);
      if (error) {
        playdate->system->logToConsole("Failed to load asteroid, error: %s",
                                       error);
      }
    }
  }

  station_bitmap_table_ =
      playdate->graphics->loadBitmapTable("data/circle_big.gif", &error);
  if (error) {
    playdate->system->logToConsole("Failed to load station, error: %s", error);
  }
}

void SpaceStation::createAsteroids(const StationArea& station_area) {
  asteroids_spatial_bin_.Clear();

  int total_num_asteroids = 0;
  for (int i = 0; i < (int)station_area.num_asteroids.size(); ++i) {
    total_num_asteroids += station_area.num_asteroids[i];
  }

  playdate_->system->logToConsole("Num asteroids created: %i",
                                  total_num_asteroids);

  asteroids_.resize(total_num_asteroids);

  int asteroid_index = 0;
  for (int type_i = 0; type_i < (int)asteroid_types_.size(); ++type_i) {
    for (int i = 0; i < station_area.num_asteroids[type_i]; ++i) {
      Asteroid& a = asteroids_[asteroid_index];

      a = Asteroid(playdate_, asteroid_types_[type_i]);

      for (size_t k = 0; k < kAsteroidInitCollisionCheckNum; ++k) {
        // random position
        auto distance = station_area.asteroids_to_base_distance +
                        ((float)StaticRandomGenerator::get().NextValue() /
                         (float)StaticRandomGenerator::get().MaxValue()) *
                            station_area.asteroids_area_distance;
        auto angle = DegToRad(StaticRandomGenerator::get().NextValue() % 360);
        a.SetPosition(Point2d(distance * cos(angle), distance * sin(angle)));

        bool intersects = false;

        std::vector<int> broad_phase;
        asteroids_spatial_bin_.Query(a.GetPosition(),
                                     Vector2d(a.GetRadius(), a.GetRadius()),
                                     broad_phase);
        for (int to_check_i = 0; to_check_i < (int)broad_phase.size();
             ++to_check_i) {
          if (Circle(a.GetPosition(), a.GetRadius())
                  .Intersect(Circle(
                      asteroids_[broad_phase[to_check_i]].GetPosition(),
                      asteroids_[broad_phase[to_check_i]].GetRadius()))) {
            intersects = true;
            break;
          }
        }

        if (!intersects) {
          break;
        }
      }

      asteroids_spatial_bin_.Add(a.GetPosition(),
                                 Vector2d(a.GetRadius(), a.GetRadius()),
                                 asteroid_index);

      ++asteroid_index;
    }
  }

  playdate_->system->logToConsole(
      "Spatial bins hashes collision: %i",
      asteroids_spatial_bin_.GetMaxHashesCollision());
}

bool SpaceStation::circleCircleCCD(const Point2d& p1, float r1,
                                   const Vector2d& move, const Point2d& p2,
                                   float r2, float& move_factor_out) {
  Vector2d move_norm = move.GetNormalized();

  Vector2d to_circle = p2 - p1;

  float move_proj = to_circle * move_norm;
  if (move_proj < 0.0f) {
    return false;
  }

  Vector2d v = to_circle - move_norm * move_proj;
  float d = v.GetLength();
  if (d > (r1 + r2)) {
    return false;
  }

  float m = move_proj - sqrtf((r1 + r2) * (r1 + r2) - d * d);

  float move_length = move.GetLength();
  if (move_length < m) {
    return false;
  }

  move_factor_out = m / move_length;

  return true;
}
