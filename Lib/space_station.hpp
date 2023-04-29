#pragma once

#include <vector>

#include "PdSymphony/all_symphony.hpp"
#include "asteroid.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_api.h"
#include "space_object.hpp"

class SpaceStation : public SpaceObject {
 public:
  SpaceStation(PlaydateAPI* playdate) : playdate_(playdate) {
    createAsteroids();
  }

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void drawDebug(const Point2d& position);
  void createAsteroids();

  static bool intersectCircles(const Point2d& p1, float r1, const Point2d& p2,
                               float r2);

  PlaydateAPI* playdate_{nullptr};

  std::vector<Asteroid> asteroids_;
};
