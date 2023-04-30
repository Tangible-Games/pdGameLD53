#include "space_station.hpp"

#include <algorithm>

bool SpaceStation::loaded = false;
std::vector<AsteroidType> SpaceStation::asteroid_types_;

void SpaceStation::Update(float dt) {
  std::for_each(asteroids_.begin(), asteroids_.end(),
                [dt](auto& a) { a.Update(dt); });
}

void SpaceStation::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));

  std::for_each(asteroids_.begin(), asteroids_.end(),
                [&](auto& a) { a.Draw(camera); });
}

void SpaceStation::drawDebug(const Point2d& position) {
  playdate_->graphics->drawLine((int)position.x - kSpaceStationSize / 2,
                                (int)position.y - kSpaceStationSize / 2,
                                (int)position.x + kSpaceStationSize / 2,
                                (int)position.y - kSpaceStationSize / 2, 3,
                                kColorWhite);
  playdate_->graphics->drawLine((int)position.x + kSpaceStationSize / 2,
                                (int)position.y - kSpaceStationSize / 2,
                                (int)position.x + kSpaceStationSize / 2,
                                (int)position.y + kSpaceStationSize / 2, 3,
                                kColorWhite);
  playdate_->graphics->drawLine((int)position.x + kSpaceStationSize / 2,
                                (int)position.y + kSpaceStationSize / 2,
                                (int)position.x - kSpaceStationSize / 2,
                                (int)position.y + kSpaceStationSize / 2, 3,
                                kColorWhite);
  playdate_->graphics->drawLine((int)position.x - kSpaceStationSize / 2,
                                (int)position.y + kSpaceStationSize / 2,
                                (int)position.x - kSpaceStationSize / 2,
                                (int)position.y - kSpaceStationSize / 2, 3,
                                kColorWhite);
}

void SpaceStation::load(PlaydateAPI* playdate) {
  asteroid_types_ = GetAsteroidTypes();
  for (auto& asteroid_type : asteroid_types_) {
    asteroid_type.bitmaps.resize(asteroid_type.models.size());
    for (int i = 0; i < (int)asteroid_type.models.size(); ++i) {
      const char* error = 0;
      asteroid_type.bitmaps[i] =
          playdate->graphics->loadBitmap(asteroid_type.models[i], &error);
      if (error) {
        playdate->system->logToConsole("Failed to load asteroid, error: %s",
                                       error);
      }
    }
  }
}

void SpaceStation::createAsteroids() {
  asteroids_spatial_bin_.Clear();

  for (int i = 0; i < (int)asteroids_.size(); ++i) {
    Asteroid& a = asteroids_[i];
    a = Asteroid(playdate_, asteroid_types_[rand() % asteroid_types_.size()]);

    for (size_t k = 0; k < kAsteroidInitCollisionCheckNum; ++k) {
      // random possition
      auto distance =
          kAsteroidToBaseAreaDistance + rand() % kAsteroidAreaDistance;
      auto angle = DegToRad(rand() % 360);
      a.SetPosition(Point2d(distance * cos(angle), distance * sin(angle)));

      bool intersects = false;

      std::vector<int> broad_phase;
      asteroids_spatial_bin_.Query(
          a.GetPosition(), Vector2d(a.GetRadius(), a.GetRadius()), broad_phase);
      for (int to_check_i = 0; to_check_i < (int)broad_phase.size();
           ++to_check_i) {
        if (Circle(a.GetPosition(), a.GetRadius())
                .Intersect(
                    Circle(asteroids_[broad_phase[to_check_i]].GetPosition(),
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
                               Vector2d(a.GetRadius(), a.GetRadius()), i);
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
