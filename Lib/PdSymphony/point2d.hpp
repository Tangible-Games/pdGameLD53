#pragma once

#include <iostream>

#include "vector2d.hpp"

namespace PdSymphony {
namespace Math {
class Point2d {
 public:
  Point2d() : x(0.0f), y(0.0f) {}

  Point2d(float new_x, float new_y) : x(new_x), y(new_y) {}

  Vector2d operator-(const Point2d& p) const {
    return Vector2d(x - p.x, y - p.y);
  }

  Point2d operator-(const Vector2d& v) const {
    return Point2d(x - v.x, y - v.y);
  }

  Point2d operator+(const Vector2d& v) const {
    return Point2d(x + v.x, y + v.y);
  }

  float x;
  float y;
};

inline bool AreOnLine(const Point2d& p1, const Point2d& p2, const Point2d& p3,
                      float eps) {
  if (fabs(p2.x - p1.x) > fabs(p2.y - p1.y)) {
    float dx1 = p2.x - p1.x;
    float dx2 = p3.x - p1.x;
    float s = dx2 / dx1;

    float dy = p2.y - p1.y;
    float y = p1.y + dy * s;

    return fabs(y - p3.y) < eps;
  } else {
    float dy1 = p2.y - p1.y;
    float dy2 = p3.y - p1.y;
    float s = dy2 / dy1;

    float dx = p2.x - p1.x;
    float x = p1.x + dx * s;

    return fabs(x - p3.x) < eps;
  }
}
}  // namespace Math
}  // namespace PdSymphony
