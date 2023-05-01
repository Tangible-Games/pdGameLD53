#pragma once

#include <iostream>

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
  float left = center.x - half_size.x;
  (void)left;
  float right = center.x + half_size.x;
  float bottom = center.y - half_size.y;
  float top = center.y + half_size.y;
  if (fabs(ray_dir_norm.x) > fabs(ray_dir_norm.y)) {
    float dx = 0.0f;
    if (ray_dir_norm.x > 0.0f) {
      dx = right - ray_start.x;
    } else {
      dx = left - ray_start.x;
    }

    float dy = ray_dir_norm.y * dx / ray_dir_norm.x;
    float y = ray_start.y + dy;

    if (y > top) {
      intersection_out.has_intersection = true;
      intersection_out.dx = 0;
      intersection_out.dy = 1;
      float new_dy = dy - (y - top);
      float new_dx = ray_dir_norm.x * new_dy / ray_dir_norm.y;
      intersection_out.p = Point2d(ray_start.x + new_dx, ray_start.y + new_dy);
    } else if (y < bottom) {
      intersection_out.has_intersection = true;
      intersection_out.dx = 0;
      intersection_out.dy = -1;
      float new_dy = dy + (bottom - y);
      float new_dx = ray_dir_norm.x * new_dy / ray_dir_norm.y;
      intersection_out.p = Point2d(ray_start.x + new_dx, ray_start.y + new_dy);
    } else {
      intersection_out.has_intersection = true;
      if (ray_dir_norm.x > 0.0f) {
        intersection_out.dx = 1;
      } else {
        intersection_out.dx = -1;
      }
      intersection_out.dy = 0;
      intersection_out.p = Point2d(ray_start.x + dx, y);
    }
  } else {
    float dy = 0.0f;
    if (ray_dir_norm.y > 0.0f) {
      dy = top - ray_start.y;
    } else {
      dy = bottom - ray_start.y;
    }

    float dx = ray_dir_norm.x * dy / ray_dir_norm.y;
    float x = ray_start.x + dx;

    if (x > right) {
      intersection_out.has_intersection = true;
      intersection_out.dx = 1;
      intersection_out.dy = 0;
      float new_dx = dx - (x - right);
      float new_dy = ray_dir_norm.y * new_dx / ray_dir_norm.x;
      intersection_out.p = Point2d(ray_start.x + new_dx, ray_start.y + new_dy);
    } else if (x < left) {
      intersection_out.has_intersection = true;
      intersection_out.dx = -1;
      intersection_out.dy = 0;
      float new_dx = dx + (left - x);
      float new_dy = ray_dir_norm.y * new_dx / ray_dir_norm.x;
      intersection_out.p = Point2d(ray_start.x + new_dx, ray_start.y + new_dy);
    } else {
      intersection_out.has_intersection = true;
      intersection_out.dx = 0;
      if (ray_dir_norm.y > 0.0f) {
        intersection_out.dy = 1;
      } else {
        intersection_out.dy = -1;
      }
      intersection_out.p = Point2d(x, ray_start.y + dy);
    }
  }
}

}  // namespace Math
}  // namespace PdSymphony
