#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "pd_api.h"
#include "space_object.hpp"

using namespace PdSymphony::Math;

class SpaceCraft : public SpaceObject {
 public:
  SpaceCraft(PlaydateAPI* playdate)
      : playdate_(playdate),
        crank_prev_angle_(playdate->system->getCrankAngle()) {}

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void updateInput(float dt);
  void drawDebug(const Point2d& position);

  PlaydateAPI* playdate_{nullptr};
  Vector2d direction_{0.0f, -1.0f};
  float rotation_speed_deg_per_sec_{360.0f};
  float acceleration_{100.0f};
  float max_linear_velocity_{1000.0f};
  float crank_prev_angle_{0.0f};
};
