#pragma once

#include <array>

#include "PdSymphony/all_symphony.hpp"
#include "asteroid.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_api.h"
#include "space_object.hpp"
#include "space_station_desc.hpp"

using namespace PdSymphony::Collision;
using namespace PdSymphony::Engine;

class SpaceStation : public SpaceObject {
 public:
  SpaceStation(PlaydateAPI* playdate) : playdate_(playdate) {
    if (!loaded) {
      load(playdate_);
      loaded = true;
    }
  }

  void Generate(const SpaceStationDesc& space_station_desc);

  void Update(float dt);
  void Draw(const Camera& camera);

  const std::vector<Asteroid>& GetAsteroids() const { return asteroids_; }

  const SpatialBin2d<int>& GetAsteroidsSpatialBin() const {
    return asteroids_spatial_bin_;
  }

 private:
  static void load(PlaydateAPI* playdate);
  void drawDebug(const Point2d& position);
  int asteroidSizeToTypeIndex(float radius) const;
  void createAsteroids(const SpaceStationDesc& space_station_desc);

  PlaydateAPI* playdate_{nullptr};

  static bool loaded;
  static std::vector<AsteroidType> asteroid_types_;
  static LCDBitmapTable* station_bitmap_table_;
  PdAnimation station_bitmap_animation_;
  std::vector<Asteroid> asteroids_;
  SpatialBin2d<int> asteroids_spatial_bin_{kAsteroidsSpatialBinsCellSize,
                                           kAsteroidsSpatialBinsCellSize,
                                           kAsteroidsSpatialBinsSize};
};
