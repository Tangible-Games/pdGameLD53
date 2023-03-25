#pragma once

#include "point2d.hpp"
#include "vector2d.hpp"

namespace PdSymphony {
namespace Math {
class Segment2d {
 public:
  Segment2d() {}

  Segment2d(const Point2d& new_p0, const Point2d new_p1)
      : p0(new_p0), p1(new_p1) {}

  bool Intersect(const Segment2d& seg1, float eps, Point2d& intersection_out) {
    float u = 0.0f;
    float v = 0.0f;
    return Intersect(seg1, eps, intersection_out, u, v);
  }

  bool Intersect(const Segment2d& seg1, float eps, Point2d& intersection_out, float& u_out, float t_out) {
    Vector2d v1 = p1 - p0;
    Vector2d v2 = seg1.p1 - seg1.p0;

    float D = v1.x * v2.y - v1.y * v2.x;
    if (fabsf(D) < eps) {
      return false;
    }

    Vector2d a = seg1.p0 - p0;

    float t = (a.x * v2.y - a.y * v2.x) / D;
    if (t < 0.0f) {
      return false;
    }
    if (t > 1.0f) {
      return false;
    }

    float u = (a.x * v1.y - a.y * v1.x) / D;
    if (u < 0.0f) {
      return false;
    }
    if (u > 1.0f) {
      return false;
    }

    intersection_out.x = p0.x + v1.x * t;
    intersection_out.y = p0.y + v1.y * t;
    u_out = u;
    t_out = t;

    return true;
  }

  Point2d p0;
  Point2d p1;
};
}  // namespace Math
}  // namespace PdSymphony
