#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_api.h"
#include "space_object.hpp"

class Asteroid : public SpaceObject {
 public:
  struct AsteroidType {
    std::vector<const char*> models;
  };

  Asteroid(PlaydateAPI* playdate, float radius)
      : playdate_(playdate), radius_(radius) {}

  float GetRadius() const { return radius_; }

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void drawDebug(const Point2d& position);

  PlaydateAPI* playdate_{nullptr};
  float radius_;
};
