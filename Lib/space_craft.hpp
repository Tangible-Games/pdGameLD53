#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_api.h"
#include "space_object.hpp"

using namespace PdSymphony::Math;

class SpaceStation;

class SpaceCraft : public SpaceObject {
 public:
  SpaceCraft(PlaydateAPI* playdate)
      : playdate_(playdate),
        crank_prev_angle_(playdate->system->getCrankAngle()) {}

  void ResetSpaceStation(SpaceStation* space_station);

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void updateInput(float dt);
  void drawDebug(const Point2d& position);

  PlaydateAPI* playdate_{nullptr};
  SpaceStation* space_station_{nullptr};
  float radius_{20.0f};
  Vector2d direction_{0.0f, -1.0f};
  const float rotation_speed_deg_per_sec_{360.0f};
  float crank_prev_angle_{0.0f};
};
