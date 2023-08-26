#include "space_station.hpp"

#include <algorithm>

#include "pd_helpers.hpp"

bool SpaceStation::loaded = false;
std::vector<AsteroidType> SpaceStation::asteroid_types_;
LCDBitmapTable* SpaceStation::station_bitmap_table_ = nullptr;

void SpaceStation::Generate(const SpaceStationDesc& space_station_desc) {
  playdate_->system->logToConsole("#SpaceStation::Generate, name: %s",
                                  space_station_desc.name.c_str());

  station_bitmap_animation_.Create(playdate_, station_bitmap_table_,
                                   "data/circle_big.gif",
                                   kSpaceStationAnimationFps);
  station_bitmap_animation_.Play(/* looped= */ true);

  createAsteroids(space_station_desc);
}

void SpaceStation::Update(float dt) {
  station_bitmap_animation_.Update(dt);

  std::for_each(asteroids_.begin(), asteroids_.end(),
                [dt](auto& a) { a.Update(dt); });
}

void SpaceStation::Draw(const Camera& camera) {
  LCDBitmap* bitmap = station_bitmap_animation_.GetBitmap();
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

int SpaceStation::asteroidSizeToTypeIndex(float radius) const {
  for (int i = 0; i < (int)asteroid_types_.size(); ++i) {
    if (fabs(asteroid_types_[i].radius - radius) < 0.01f) {
      return i;
    }
  }

  return 0;
}

void SpaceStation::createAsteroids(const SpaceStationDesc& space_station_desc) {
  asteroids_spatial_bin_.Clear();

  asteroids_.resize(space_station_desc.asteroids.size());
  for (int i = 0; i < (int)space_station_desc.asteroids.size(); ++i) {
    Asteroid& a = asteroids_[i];

    float asteroid_radius = space_station_desc.asteroids[i].radius;
    int asteroid_type_index = asteroidSizeToTypeIndex(asteroid_radius);

    a = Asteroid(playdate_, asteroid_types_[asteroid_type_index]);
    a.SetPosition(space_station_desc.asteroids[i].pos);

    asteroids_spatial_bin_.Add(a.GetPosition(),
                               Vector2d(a.GetRadius(), a.GetRadius()), i);
  }

  playdate_->system->logToConsole("Num asteroids created: %i",
                                  asteroids_.size());

  playdate_->system->logToConsole(
      "Spatial bins hashes collision: %i",
      asteroids_spatial_bin_.GetMaxHashesCollision());
}
