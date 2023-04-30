#pragma once

#include <array>

#include "PdSymphony/all_symphony.hpp"
#include "asteroid.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_api.h"
#include "space_object.hpp"

class SpaceStation : public SpaceObject {
 public:
  SpaceStation(PlaydateAPI* playdate) : playdate_(playdate) {
    if (!loaded) {
      load(playdate_);
      loaded = true;
    }
  }

  void Generate(uint32_t seed) {
    srand(seed);
    createAsteroids();
  }

  void Update(float dt);
  void Draw(const Camera& camera);

  const std::array<Asteroid, kAsteroidsNum>& GetAsteroids() const {
    return asteroids_;
  }

 private:
  static void load(PlaydateAPI* playdate);
  void drawDebug(const Point2d& position);
  void createAsteroids();

  static bool circleCircleCCD(const Point2d& p1, float r1, const Vector2d& move,
                              const Point2d& p2, float r2,
                              float& move_factor_out);

  PlaydateAPI* playdate_{nullptr};

  static bool loaded;
  static std::vector<AsteroidType> asteroid_types_;
  std::array<Asteroid, kAsteroidsNum> asteroids_;
};
