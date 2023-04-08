#include "transformation_matrix3d.hpp"

#include <gtest/gtest.h>

TEST(TransformationMatrix3d, IdentityMatrix) {
  PdSymphony::Math::TransformationMatrix3d m;

  PdSymphony::Math::Point3d p = m * PdSymphony::Math::Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_EQ(1.0f, p.x);
  ASSERT_EQ(2.0f, p.y);
  ASSERT_EQ(3.0f, p.z);

  PdSymphony::Math::Vector3d v = m * PdSymphony::Math::Vector3d(1.0f, 2.0f, 3.0f);
  ASSERT_EQ(1.0f, v.x);
  ASSERT_EQ(2.0f, v.y);
  ASSERT_EQ(3.0f, v.z);
}

TEST(TransformationMatrix3d, ScaleMatrix) {
  PdSymphony::Math::TransformationMatrix3d m;
  m.MakeScale(PdSymphony::Math::Vector3d(2.0f, 3.0f, 4.0f));

  PdSymphony::Math::Point3d p = m * PdSymphony::Math::Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_EQ(2.0f, p.x);
  ASSERT_EQ(6.0f, p.y);
  ASSERT_EQ(12.0f, p.z);
}

TEST(TransformationMatrix3d, TranslationMatrix) {
  PdSymphony::Math::TransformationMatrix3d m;
  m.MakeTranslation(PdSymphony::Math::Vector3d(2.0f, 3.0f, 4.0f));

  PdSymphony::Math::Point3d p = m * PdSymphony::Math::Point3d(1.0f, 2.0f, 3.0f);
  ASSERT_EQ(3.0f, p.x);
  ASSERT_EQ(5.0f, p.y);
  ASSERT_EQ(7.0f, p.z);
}
