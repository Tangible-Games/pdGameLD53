#include "transformation_matrix3d.hpp"

#include <gtest/gtest.h>

TEST(TransformationMatrix3d, IdentityMatrix) {
  PdSymphony::Math::TransformationMatrix3d m;

  PdSymphony::Math::Point3d p = m * PdSymphony::Math::Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(1.0f, p.x, 0.01f);
  ASSERT_NEAR(2.0f, p.y, 0.01f);
  ASSERT_NEAR(3.0f, p.z, 0.01f);

  PdSymphony::Math::Vector3d v = m * PdSymphony::Math::Vector3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(1.0f, v.x, 0.01f);
  ASSERT_NEAR(2.0f, v.y, 0.01f);
  ASSERT_NEAR(3.0f, v.z, 0.01f);
}

TEST(TransformationMatrix3d, ScaleMatrix) {
  PdSymphony::Math::TransformationMatrix3d m;
  m.MakeScale(PdSymphony::Math::Vector3d(2.0f, 3.0f, 4.0f));

  PdSymphony::Math::Point3d p = m * PdSymphony::Math::Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(2.0f, p.x, 0.01f);
  ASSERT_NEAR(6.0f, p.y, 0.01f);
  ASSERT_NEAR(12.0f, p.z, 0.01f);
}

TEST(TransformationMatrix3d, TranslationMatrix) {
  PdSymphony::Math::TransformationMatrix3d m;
  m.MakeTranslation(PdSymphony::Math::Vector3d(2.0f, 3.0f, 4.0f));

  PdSymphony::Math::Point3d p = m * PdSymphony::Math::Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(3.0f, p.x, 0.01f);
  ASSERT_NEAR(5.0f, p.y, 0.01f);
  ASSERT_NEAR(7.0f, p.z, 0.01f);
}

TEST(TransformationMatrix3d, PerspectiveMatrix) {
  float screen_width = 400.0f;
  float screen_height = 200.0f;

  PdSymphony::Math::TransformationMatrix3d m;
  m.MakePerspective(/* horizontal_fov_deg= */ 90.0f, screen_width / screen_height, 1.0f, 1000.0f);

  PdSymphony::Math::Point3d p = m * PdSymphony::Math::Point3d(0.0f, 0.0f, -1.0f);
  ASSERT_NEAR(0.0f, p.x, 0.01f);
  ASSERT_NEAR(0.0f, p.y, 0.01f);
  ASSERT_NEAR(-1.0f, p.z, 0.01f);

  p = m * PdSymphony::Math::Point3d(0.0f, 0.0f, -1000.0f);
  ASSERT_NEAR(0.0f, p.x, 0.01f);
  ASSERT_NEAR(0.0f, p.y, 0.01f);
  ASSERT_NEAR(1000.0f, p.z, 0.01f);

  p = m * PdSymphony::Math::Point3d(1000.0f, 0.0f, -1000.0f);
  ASSERT_NEAR(1000.0f, p.x, 0.01f);
  ASSERT_NEAR(0.0f, p.y, 0.01f);

  p = m * PdSymphony::Math::Point3d(0.0f, 1000.0f, -1000.0f);
  ASSERT_NEAR(0.0f, p.x, 0.01f);
  ASSERT_NEAR(1000.0f * screen_height / screen_width, p.y, 0.01f);
}

TEST(TransformationMatrix3d, Multiply) {
  PdSymphony::Math::TransformationMatrix3d identity;

  PdSymphony::Math::TransformationMatrix3d tr;
  tr.MakeTranslation(1.0f, 2.0f, 3.0f);

  PdSymphony::Math::Point3d p = (identity * tr) * PdSymphony::Math::Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(2.0f, p.x, 0.01f);
  ASSERT_NEAR(4.0f, p.y, 0.01f);
  ASSERT_NEAR(6.0f, p.z, 0.01f);

  p = (tr * identity) * PdSymphony::Math::Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(2.0f, p.x, 0.01f);
  ASSERT_NEAR(4.0f, p.y, 0.01f);
  ASSERT_NEAR(6.0f, p.z, 0.01f);

  PdSymphony::Math::TransformationMatrix3d s;
  s.MakeScale(2.0f, 3.0f, 4.0f);

  p = (s * tr) * PdSymphony::Math::Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(4.0f, p.x, 0.01f);
  ASSERT_NEAR(12.0f, p.y, 0.01f);
  ASSERT_NEAR(24.0f, p.z, 0.01f);

  p = (tr * s) * PdSymphony::Math::Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_NEAR(3.0f, p.x, 0.01f);
  ASSERT_NEAR(8.0f, p.y, 0.01f);
  ASSERT_NEAR(15.0f, p.z, 0.01f);
}
