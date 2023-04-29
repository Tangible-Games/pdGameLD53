#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "pd_api.h"

class SpaceStation {
 public:
  SpaceStation(PlaydateAPI* playdate) : playdate_(playdate) {}

  void SetPosition(const Point2d& position) { position_ = position; }

  const Point2d& GetPosition() const { return position_; }

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void drawDebug(const Point2d& position);

  PlaydateAPI* playdate_{nullptr};
  Point2d position_;
};
