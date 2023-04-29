#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "pd_api.h"
#include "space_object.hpp"

class SpaceStation : public SpaceObject {
 public:
  SpaceStation(PlaydateAPI* playdate) : playdate_(playdate) {}

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void drawDebug(const Point2d& position);

  PlaydateAPI* playdate_{nullptr};
};
