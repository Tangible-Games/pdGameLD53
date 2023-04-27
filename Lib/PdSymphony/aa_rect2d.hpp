#pragma once

#include "point2d.hpp"
#include "vector2d.hpp"

namespace PdSymphony {
namespace Math {
class AARect2d {
 public:
  AARect2d() {}

  AARect2d(const Point2d& new_center, const Vector2d& new_half_size)
      : center(new_center), half_size(new_half_size) {}

  Point2d BottomLeft() const { return center - half_size; }

  Point2d TopRight() const { return center + half_size; }

  bool IsPointInside(const Point2d& p) const {
    Point2d bottom_left = BottomLeft();
    Point2d top_right = TopRight();
    return (p.x > bottom_left.x && p.y > bottom_left.y && p.x < top_right.x &&
            p.y < top_right.y);
  }

  bool IsPointOnLeftBorder(const Point2d& p, float eps) const {
    float left = center.x - half_size.x;
    float bottom = center.y - half_size.y;
    float top = center.y + half_size.y;
    return ((p.x > (left - eps)) && p.x < (left + eps) &&
            p.y > (bottom - eps) && p.y < (top - eps));
  }

  bool IsPointOnRightBorder(const Point2d& p, float eps) const {
    float right = center.x + half_size.x;
    float bottom = center.y - half_size.y;
    float top = center.y + half_size.y;
    return ((p.x > (right - eps)) && p.x < (right + eps) &&
            p.y > (bottom - eps) && p.y < (top - eps));
  }

  bool IsPointOnTopBorder(const Point2d& p, float eps) const {
    float left = center.x - half_size.x;
    float right = center.x + half_size.x;
    float top = center.y + half_size.y;
    return (p.x > (left - eps) && p.x < (right + eps) && p.y > (top - eps) &&
            p.y < (top + eps));
  }

  bool IsPointOnBottomBorder(const Point2d& p, float eps) const {
    float left = center.x - half_size.x;
    float right = center.x + half_size.x;
    float bottom = center.y - half_size.y;
    return (p.x > (left - eps) && p.x < (right + eps) && p.y > (bottom - eps) &&
            p.y < (bottom + eps));
  }

  struct FromInsideIntersection {
    bool has_intersection;
    int dx;
    int dy;
    Point2d p;
  };

  void IntersectRayFromInside(const Point2d& ray_start,
                              const Vector2d& ray_dir_norm,
                              FromInsideIntersection& intersection_out);

  Point2d center;
  Vector2d half_size;
};

inline void AARect2d::IntersectRayFromInside(
    const Point2d& ray_start, const Vector2d& ray_dir_norm,
    FromInsideIntersection& intersection_out) {
  (void)ray_start;
  (void)ray_dir_norm;
  (void)intersection_out;
}

}  // namespace Math
}  // namespace PdSymphony
