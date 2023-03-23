#ifndef __PD_SYMPHONY_MATH_VECTOR_H_
#define __PD_SYMPHONY_MATH_VECTOR_H_

namespace PdSymphony {
namespace Math {
class Vector2d {
 public:
  Vector2d() : x(0.0f), y(0.0f) {}

  Vector2d(float new_x, float new_y) : x(new_x), y(new_y) {}

  Vector2d operator+(const Vector2d& rhv) {
    return Vector2d(x + rhv.x, y + rhv.y);
  }

  Vector2d operator-(const Vector2d& rhv) {
    return Vector2d(x - rhv.x, y - rhv.y);
  }

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

  void Rotate(float angle_rad) {
    float c = cosf(angle_rad);
    float s = sinf(angle_rad);
    x = c * x - s * y;
    y = s * x + c * y;
  }

  Vector2d GetRotated(float angle_rad) const {
    Vector2d v(x, y);
    v.Rotate(angle_rad);
    return v;
  }

  float x;
  float y;
};
}  // namespace Math
}  // namespace PdSymphony

#endif
