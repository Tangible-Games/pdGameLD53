#pragma once

#include <math.h>

namespace PdSymphony {
namespace Math {
class Vector2d {
 public:
  Vector2d() : x(0.0f), y(0.0f) {}

  Vector2d(float new_x, float new_y) : x(new_x), y(new_y) {}

  Vector2d operator+(const Vector2d &rhv) const {
    return Vector2d(x + rhv.x, y + rhv.y);
  }

  Vector2d operator-(const Vector2d &rhv) const {
    return Vector2d(x - rhv.x, y - rhv.y);
  }

  Vector2d operator*(float v) { return Vector2d(x * v, y * v); }

  float operator*(const Vector2d &v) const { return x * v.x + y * v.y; }

  float GetLengthSq() const { return x * x + y * y; }

  float GetLength() const { return sqrtf(GetLengthSq()); }

  void MakeNormalized(float eps) {
    float l = GetLength();
    if (l < eps) {
      x = 0.0f;
      y = 0.0f;
    } else {
      x = x / l;
      y = y / l;
    }
  }

  void MakeNormalized() {
    float l = GetLength();
    x = x / l;
    y = y / l;
  }

  Vector2d GetNormalized() const {
    Vector2d v(x, y);
    v.MakeNormalized();
    return v;
  }

  void Rotate(float angle_rad) { Rotate(cosf(angle_rad), sinf(angle_rad)); }

  Vector2d GetRotated(float angle_rad) const {
    Vector2d v(x, y);
    v.Rotate(angle_rad);
    return v;
  }

  void Rotate(float cos_val, float sin_val) {
    float new_x = cos_val * x - sin_val * y;
    float new_y = sin_val * x + cos_val * y;
    x = new_x;
    y = new_y;
  }

  Vector2d GetRotated(float cos_val, float sin_val) const {
    Vector2d v(x, y);
    v.Rotate(cos_val, sin_val);
    return v;
  }

  float x;
  float y;
};
}  // namespace Math
}  // namespace PdSymphony
