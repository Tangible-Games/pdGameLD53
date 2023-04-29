#pragma once

#include "PdSymphony/all_symphony.hpp"

struct SpaceObject {
  void SetPosition(const Point2d& position) { position_ = position; }
  const Point2d& GetPosition() const { return position_; }

  Point2d position_;
  Vector2d velocity_;
};