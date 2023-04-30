#pragma once

#include <array>

#include "PdSymphony/all_symphony.hpp"
#include "asteroid.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_api.h"
#include "space_object.hpp"

using namespace PdSymphony::Collision;

class SpaceStation : public SpaceObject {
 public:
  SpaceStation(PlaydateAPI* playdate) : playdate_(playdate) {
    if (!loaded) {
      load(playdate_);
      loaded = true;
    }
  }

  void Generate(const StationArea& station_area);

  void Update(float dt);
  void Draw(const Camera& camera);

  const std::vector<Asteroid>& GetAsteroids() const { return asteroids_; }

  const SpatialBin2d<int>& GetAsteroidsSpatialBin() const {
    return asteroids_spatial_bin_;
  }

 private:
  static void load(PlaydateAPI* playdate);
  void drawDebug(const Point2d& position);
  void createAsteroids(const StationArea& station_area);

  static bool circleCircleCCD(const Point2d& p1, float r1, const Vector2d& move,
                              const Point2d& p2, float r2,
                              float& move_factor_out);

  PlaydateAPI* playdate_{nullptr};

  static bool loaded;
  static std::vector<AsteroidType> asteroid_types_;
  std::vector<Asteroid> asteroids_;
  SpatialBin2d<int> asteroids_spatial_bin_{kAsteroidsSpatialBinsCellSize,
                                           kAsteroidsSpatialBinsCellSize,
                                           kAsteroidsSpatialBinsSize};
};
