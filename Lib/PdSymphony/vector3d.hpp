#pragma once

#include "vector2d.hpp"
#include <math.h>

namespace PdSymphony {
namespace Math {
class Vector3d {
public:
  Vector3d() : x(0.0f), y(0.0f), z(0.0f) {}

  Vector3d(float new_x, float new_y, float new_z)
      : x(new_x), y(new_y), z(new_z) {}

  Vector3d operator+(const Vector3d &rhv) const {
    return Vector3d(x + rhv.x, y + rhv.y, z + rhv.z);
  }

  Vector3d operator-(const Vector3d &rhv) const {
    return Vector3d(x - rhv.x, y - rhv.y, z - rhv.z);
  }

  Vector3d operator*(float v) { return Vector3d(x * v, y * v, z * v); }

  float operator*(const Vector3d &v) const {
    return x * v.x + y * v.y + z * v.z;
  }

  Vector3d Cross(const Vector3d &rhv) const {
    return Vector3d(y * rhv.z - z * rhv.y, z * rhv.x - x * rhv.z,
                    x * rhv.y - y * rhv.x);
  }

  float GetLengthSq() const { return x * x + y * y + z * z; }

  float GetLength() const { return sqrtf(GetLengthSq()); }

  void MakeNormalized(float eps) {
    float l = GetLength();
    if (l < eps) {
      x = 0.0f;
      y = 0.0f;
      z = 0.0f;
    } else {
      x = x / l;
      y = y / l;
      z = z / l;
    }
  }

  void MakeNormalized() {
    float l = GetLength();
    x = x / l;
    y = y / l;
    z = z / l;
  }

  Vector3d GetNormalized() const {
    Vector3d v(x, y, z);
    v.MakeNormalized();
    return v;
  }

#pragma pack(push)
#pragma pack(1)
  float x;
  float y;
  float z;
#pragma pack(pop)
};
} // namespace Math
} // namespace PdSymphony
