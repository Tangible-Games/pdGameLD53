#include "angle.hpp"
#include "vector2d.hpp"

#include <gtest/gtest.h>

TEST(Vector2d, PlusMinus) {
  PdSymphony::Math::Vector2d v1(1.0f, 2.0f);
  PdSymphony::Math::Vector2d v2(5.0f, 7.0f);

  PdSymphony::Math::Vector2d v3 = v1 + v2;
  ASSERT_NEAR(6.0f, v3.x, 0.001f);
  ASSERT_NEAR(9.0f, v3.y, 0.001f);

  PdSymphony::Math::Vector2d v4 = v1 - v2;
  ASSERT_NEAR(-4.0f, v4.x, 0.001f);
  ASSERT_NEAR(-5.0f, v4.y, 0.001f);
}

TEST(Vector2d, Rotation) {
  PdSymphony::Math::Vector2d v(0.0f, 1.0f);

  PdSymphony::Math::Vector2d v1 =
      v.GetRotated(PdSymphony::Math::DegToRad(90.0f));
  ASSERT_NEAR(-1.0f, v1.x, 0.001f);
  ASSERT_NEAR(0.0f, v1.y, 0.001f);

  PdSymphony::Math::Vector2d v2 =
      v.GetRotated(PdSymphony::Math::DegToRad(-90.0f));
  ASSERT_NEAR(1.0f, v2.x, 0.001f);
  ASSERT_NEAR(0.0f, v2.y, 0.001f);
}
