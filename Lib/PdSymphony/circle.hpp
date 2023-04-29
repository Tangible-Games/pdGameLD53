#pragma once

#include "point2d.hpp"
#include "vector2d.hpp"

namespace PdSymphony {
namespace Math {
class Circle {
 public:
  Circle() {}

  Circle(const Point2d& new_center, float new_radius)
      : center(new_center), radius(new_radius) {}

  bool Intersect(const Circle& circle) const {
    Vector2d v = circle.center - center;
    if (v.GetLength() > (circle.radius + radius)) {
      return false;
    }
    return true;
  }

  Point2d center;
  float radius{0.0f};
};
}  // namespace Math
}  // namespace PdSymphony
