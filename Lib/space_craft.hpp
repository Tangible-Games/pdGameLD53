#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "pd_api.h"

using namespace PdSymphony::Math;

class SpaceCraft {
 public:
  SpaceCraft(PlaydateAPI* playdate) : playdate_(playdate) {}

  void UpdateAndDraw(float dt, const Camera& camera);

 private:
  void updateInput(float dt);
  void drawDebug(const Point2d& position);

  PlaydateAPI* playdate_{nullptr};
  Point2d position_;
  Vector2d direction_;
};
