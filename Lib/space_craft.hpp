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
  Vector2d direction_{0.0f, -1.0f};
  Vector2d velocity_;
  float rotation_speed_deg_per_sec_{360.0f};
  float acceleration_{100.0f};
  float max_linear_velocity_{1000.0f};
};
