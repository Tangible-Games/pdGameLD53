#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "pd_api.h"
#include "space_object.hpp"

class Asteroid : public SpaceObject {
 public:
  Asteroid(PlaydateAPI* playdate, size_t size)
      : playdate_(playdate), size_(size) {}

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void drawDebug(const Point2d& position);

  PlaydateAPI* playdate_{nullptr};
  size_t size_;
};
