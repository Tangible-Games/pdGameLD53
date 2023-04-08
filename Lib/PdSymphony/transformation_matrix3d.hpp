#pragma once

#include "angle.hpp"
#include "vector3d.hpp"
#include "point3d.hpp"

namespace PdSymphony {
namespace Math {
class TransformationMatrix3d {
 public:
  static const int kNumColumns = 4;
  static const int kNumRows = 4;
  static const int kSize = kNumColumns * kNumRows;

  TransformationMatrix3d() { MakeIdentity(); }

  explicit TransformationMatrix3d(bool make_identity) {
    if (make_identity) {
      MakeIdentity();
    }
  }

  TransformationMatrix3d(const float* new_matrix) {
    float* m = &m11;
    for (int i = 0; i < kSize; ++i) {
      m[i] = new_matrix[i];
    }
  }

  void MakeZero() {
    float* m = &m11;
    for (int i = 0; i < kSize; ++i) {
      m[i] = 0.0f;
    }
  }

  void MakeIdentity() {
    MakeZero();
    m11 = 1.0f;
    m22 = 1.0f;
    m33 = 1.0f;
    m44 = 1.0f;
  }

  void MakeScale(float scale_x, float scale_y, float scale_z) {
    MakeZero();
    m11 = scale_x;
    m22 = scale_y;
    m33 = scale_z;
    m44 = 1.0f;
  }

  void MakeScale(const Vector3d& scale) {
    MakeScale(scale.x, scale.y, scale.z);
  }

  void MakeTranslation(float translate_x, float translate_y, float translate_z) {
    MakeIdentity( );
    m41 = translate_x;
    m42 = translate_y;
    m43 = translate_z;
  }

  void MakeTranslation(const Vector3d& translate) {
    MakeTranslation(translate.x, translate.y, translate.z);
  }

  // TODO(truvorskameikin): Implement MakeRotation. Need to implememnt Quaternion and Rotation classes.

  void MakePerspective(float horizontal_fov_deg, float aspect_ratio, float near_z, float far_z) {
    float e = 1.0f / tanf(DegToRad(horizontal_fov_deg) / 2.0f);

    MakeZero( );
    m11 = e;
    m22 = e / aspect_ratio;
    m33 = (near_z + far_z) / (near_z - far_z);
    m34 = -1.0f;
    m43 = 2.0f * near_z * far_z / (near_z - far_z);
  }

  void MakeLookAt(const Point3d& eye, const Vector3d& forward_norm, const Vector3d& up_norm) {
    Vector3d s = forward_norm.Cross(up_norm);
    Vector3d u = s.Cross(forward_norm);

    TransformationMatrix3d m1;
    m1.m11 = s.x;
    m1.m12 = u.x;
    m1.m13 = -forward_norm.x;
    m1.m21 = s.y;
    m1.m22 = u.y;
    m1.m23 = -forward_norm.y;
    m1.m31 = s.z;
    m1.m32 = u.z;
    m1.m33 = -forward_norm.z;

    TransformationMatrix3d m2(/* make_identity= */ false);
    m2.MakeTranslation(-eye.x, -eye.y, -eye.z);

    *this = m1 * m2;
  }

  TransformationMatrix3d operator*(const TransformationMatrix3d& rhv) const {
    return Multiply(rhv);
  }

  TransformationMatrix3d Multiply(const TransformationMatrix3d& rhv) const {
    TransformationMatrix3d result(/* make_identity= */ false);
    float* result_m = &result.m11;

    const float* m = &m11;
    const float* rhv_m = &rhv.m11;
    for( int i = 0; i < 4; ++i ) {
      for( int j = 0; j < 4; ++j ) {
        result_m[i * 4 + j] = m[0 * 4 + j] * rhv_m[i * 4 + 0] +
                    m[1 * 4 + j] * rhv_m[ i * 4 + 1 ] +
                    m[2 * 4 + j] * rhv_m[ i * 4 + 2 ] +
                    m[3 * 4 + j] * rhv_m[ i * 4 + 3 ];
      }
    }

    return result;
  }

  Point3d operator*(const Point3d& p) const { return Transform(p, 1.0f); }

  Point3d Transform(const Point3d& p) const { return Transform(p, 1.0f); }

  Point3d Transform(const Point3d& p, float w) const  {
    Point3d result;
    transform(&p.x, w, &result.x);
    return result;
  }

  Vector3d operator*(const Vector3d& p) const { return Transform(p, 1.0f); }

  Vector3d Transform(const Vector3d& p) const { return Transform(p, 1.0f); }

  Vector3d Transform(const Vector3d& v, float w) const  {
    Vector3d result;
    transform(&v.x, w, &result.x);
    return result;
  }

#pragma pack(push)
#pragma pack(1)
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
#pragma pack(pop)

 private:
  void transform(const float* vec, float w, float* vec_out) const {
    const float* m = &m11;
    vec_out[0] = vec[0] * m[0 * 4 + 0] + vec[1] * m[1 * 4 + 0] +
                          vec[2] * m[2 * 4 + 0] + w * m[3 * 4 + 0];
    vec_out[1] = vec[0] * m[0 * 4 + 1] + vec[1] * m[1 * 4 + 1] +
                          vec[2] * m[2 * 4 + 1] + w * m[3 * 4 + 1];
    vec_out[2] = vec[0] * m[0 * 4 + 2] + vec[1] * m[1 * 4 + 2] +
                          vec[2] * m[2 * 4 + 2] + w * m[3 * 4 + 2];
  }
};
}  // namespace Math
}  // namespace PdSymphony
