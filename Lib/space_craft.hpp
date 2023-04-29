#pragma once

#include "pd_api.h"
#include "PdSymphony/all_symphony.hpp"

#include "camera.hpp"

using namespace PdSymphony::Math;

class SpaceCraft {
 public:
  SpaceCraft(PlaydateAPI* playdate) : playdate_(playdate) {}

  void UpdateAndDraw(float dt, const Camera& camera);

 private:
  void drawDebug(const Point2d& position);

  PlaydateAPI* playdate_{nullptr};
  Point2d position_;
};
