#ifndef __PD_SYMPHONY_MATH_POINT_H_
#define __PD_SYMPHONY_MATH_POINT_H_

#include "vector2d.hpp"

namespace PdSymphony {
namespace Math {
class Point2d {
 public:
  Point2d() : x(0.0f), y(0.0f) {}

  Point2d(float new_x, float new_y) : x(new_x), y(new_y) {}

  Vector2d operator-(const Point2d& p) { return Vector2d(x - p.x, y - p.y); }

  Point2d operator-(const Vector2d& v) { return Point2d(x - v.x, y - v.y); }

  Point2d operator+(const Vector2d& v) { return Point2d(x + v.x, y + v.y); }

  float x;
  float y;
};
}  // namespace Math
}  // namespace PdSymphony

#endif
