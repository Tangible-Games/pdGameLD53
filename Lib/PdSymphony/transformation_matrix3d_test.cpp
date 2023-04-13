#include "transformation_matrix3d.hpp"

#include <gtest/gtest.h>

#include "angle.hpp"
#include "point2d.hpp"
#include "segment2d.hpp"

using namespace PdSymphony::Math;

TEST(TransformationMatrix3d, IdentityMatrix) {
  TransformationMatrix3d m;

  Point3d p = m * Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(1.0f, p.x, 0.01f);
  ASSERT_NEAR(2.0f, p.y, 0.01f);
  ASSERT_NEAR(3.0f, p.z, 0.01f);

  Vector3d v = m * Vector3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(1.0f, v.x, 0.01f);
  ASSERT_NEAR(2.0f, v.y, 0.01f);
  ASSERT_NEAR(3.0f, v.z, 0.01f);
}

TEST(TransformationMatrix3d, ScaleMatrix) {
  TransformationMatrix3d m;
  m.MakeScale(Vector3d(2.0f, 3.0f, 4.0f));

  Point3d p = m * Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(2.0f, p.x, 0.01f);
  ASSERT_NEAR(6.0f, p.y, 0.01f);
  ASSERT_NEAR(12.0f, p.z, 0.01f);
}

TEST(TransformationMatrix3d, TranslationMatrix) {
  TransformationMatrix3d m;
  m.MakeTranslation(Vector3d(2.0f, 3.0f, 4.0f));

  Point3d p = m * Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(3.0f, p.x, 0.01f);
  ASSERT_NEAR(5.0f, p.y, 0.01f);
  ASSERT_NEAR(7.0f, p.z, 0.01f);
}

TEST(TransformationMatrix3d, Multiply) {
  TransformationMatrix3d identity;

  TransformationMatrix3d tr;
  tr.MakeTranslation(1.0f, 2.0f, 3.0f);

  Point3d p = (identity * tr) * Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(2.0f, p.x, 0.01f);
  ASSERT_NEAR(4.0f, p.y, 0.01f);
  ASSERT_NEAR(6.0f, p.z, 0.01f);

  p = (tr * identity) * Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(2.0f, p.x, 0.01f);
  ASSERT_NEAR(4.0f, p.y, 0.01f);
  ASSERT_NEAR(6.0f, p.z, 0.01f);

  TransformationMatrix3d s;
  s.MakeScale(2.0f, 3.0f, 4.0f);

  p = (s * tr) * Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(4.0f, p.x, 0.01f);
  ASSERT_NEAR(12.0f, p.y, 0.01f);
  ASSERT_NEAR(24.0f, p.z, 0.01f);

  p = (tr * s) * Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(3.0f, p.x, 0.01f);
  ASSERT_NEAR(8.0f, p.y, 0.01f);
  ASSERT_NEAR(15.0f, p.z, 0.01f);
}

TEST(TransformationMatrix3d, LookAtMatrix) {
  Point3d eye(2.0f, 3.0f, 1.0f);
  Vector3d forward = Vector3d(1.0f, 1.0f, 0.0f).GetNormalized();
  Vector3d up(0.0f, 0.0f, 1.0f);

  TransformationMatrix3d m;
  m.MakeLookAt(eye, forward, up);

  Point3d p = m * Point3d(3.0f, 4.0f, 0.0f);
  ASSERT_NEAR(0.0f, p.x, 0.01f);
  ASSERT_NEAR(-1.0f, p.y, 0.01f);
  ASSERT_NEAR(-sqrtf(2.0f), p.z, 0.01f);

  p = m * Point3d(2.0f, 4.0f, 1.0f);
  ASSERT_NEAR(-cosf(DegToRad(45.0f)), p.x, 0.01f);
  ASSERT_NEAR(0.0f, p.y, 0.01f);
  ASSERT_NEAR(-cosf(DegToRad(45.0f)), p.z, 0.01f);
}

TEST(TransformationMatrix3d, LookAtMatrix2) {
  Point3d eye(2.0f, 3.0f, 1.0f);
  Vector3d forward = Vector3d(1.0f, 1.0f, 0.0f).GetNormalized();
  Vector3d up(0.0f, 0.0f, 1.0f);

  TransformationMatrix3d m;
  m.MakeLookAt(eye, forward, up);

  Point3d p1(1.0f, 4.0f, 0.0f);
  Point3d p2(2.0f, 4.0f, 1.0f);
  Point3d p3(3.0f, 4.0f, 2.0f);

  Point3d pp1 = m * p1;
  Point3d pp2 = m * p2;
  Point3d pp3 = m * p3;

  bool result = AreOnLine(Point2d(pp1.x, pp1.y), Point2d(pp2.x, pp2.y),
                          Point2d(pp3.x, pp3.y), 0.0001f);
  ASSERT_TRUE(result);
}
