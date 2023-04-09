#pragma once

#include "vector3d.hpp"

namespace PdSymphony {
namespace Math {
class Point3d {
 public:
  Point3d() : x(0.0f), y(0.0f), z(0.0f) {}

  Point3d(float new_x, float new_y, float new_z)
      : x(new_x), y(new_y), z(new_z) {}

  Vector3d operator-(const Point3d &p) const {
    return Vector3d(x - p.x, y - p.y, z - p.z);
  }

  Point3d operator-(const Vector3d &v) const {
    return Point3d(x - v.x, y - v.y, z - v.z);
  }

  Point3d operator+(const Vector3d &v) const {
    return Point3d(x + v.x, y + v.y, z + v.z);
  }

#pragma pack(push)
#pragma pack(1)
  float x;
  float y;
  float z;
#pragma pack(pop)
};
}  // namespace Math
}  // namespace PdSymphony
