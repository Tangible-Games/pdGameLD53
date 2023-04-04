#ifndef __PD_SYMPHONY_MATH_TRANSFORMATION_MATRIX_H_
#define __PD_SYMPHONY_MATH_TRANSFORMATION_MATRIX_H_

#include "angle.hpp"
#include "vector3d.hpp"

namespace PdSymphony {
namespace Math {
class TransformationMatrix3d {
 public:
  static const int kNumColumns = 4;
  static const int kNumRows = 4;
  static const int kSize = kNumColumns * kNumRows;

  TransformationMatrix3d() { MakeIdentity(); }

  TransformationMatrix3d(float* new_matrix) {
    for (int i = 0; i < kSize; ++i) {
      m[i] = new_matrix[i];
    }
  }

  void MakeIdentity() {
    for (int i = 0; i < kSize; ++i) {
      m[i] = 0.0f;
    }
    m11 = 1.0f;
    m22 = 1.0f;
    m33 = 1.0f;
    m44 = 1.0f;
  }

  Position3d operator*(const Position3d& p) const { return Apply(p, 1.0f); }

  Position3d Apply(const Position3d& p) { return Apply(p, 1.0f); }

  Position3d Apply(const Position3d& p, float w) {
    Position3d result(p.x * m[0 * 4 + 0] + p.y * m[1 * 4 + 0] +
                          p.z * m[2 * 4 + 0] + w * m[3 * 4 + 0],
                      p.x * m[0 * 4 + 1] + p.y * m[1 * 4 + 1] +
                          p.z * m[2 * 4 + 1] + w * m[3 * 4 + 1],
                      p.x * m[0 * 4 + 2] + p.y * m[1 * 4 + 2] +
                          p.z * m[2 * 4 + 2] + w * m[3 * 4 + 2]);
    return result;
  }

  union {
    float m[kSize];

    struct {
      float m11;
      float m12;
      float m13;
      float m14;

      float m21;
      float m22;
      float m23;
      float m24;

      float m31;
      float m32;
      float m33;
      float m34;

      float m41;
      float m42;
      float m43;
      float m44;
    };
  }
}
}  // namespace Math
}  // namespace PdSymphony

#endif
