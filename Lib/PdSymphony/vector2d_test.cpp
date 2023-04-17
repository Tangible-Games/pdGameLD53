#include "vector2d.hpp"

#include <gtest/gtest.h>

#include "angle.hpp"

using namespace PdSymphony::Math;

TEST(Vector2d, PlusMinus) {
  Vector2d v1(1.0f, 2.0f);
  Vector2d v2(5.0f, 7.0f);

  Vector2d v3 = v1 + v2;
  ASSERT_NEAR(6.0f, v3.x, 0.001f);
  ASSERT_NEAR(9.0f, v3.y, 0.001f);

  Vector2d v4 = v1 - v2;
  ASSERT_NEAR(-4.0f, v4.x, 0.001f);
  ASSERT_NEAR(-5.0f, v4.y, 0.001f);
}

TEST(Vector2d, Rotation) {
  Vector2d v(0.0f, 1.0f);

  Vector2d v1 = v.GetRotated(DegToRad(90.0f));
  ASSERT_NEAR(-1.0f, v1.x, 0.001f);
  ASSERT_NEAR(0.0f, v1.y, 0.001f);

  Vector2d v2 = v.GetRotated(DegToRad(-90.0f));
  ASSERT_NEAR(1.0f, v2.x, 0.001f);
  ASSERT_NEAR(0.0f, v2.y, 0.001f);
}

TEST(Vector2d, NormalizedVectorIsStillNormalized) {
  Vector2d v(5.0f, 7.0f);
  Vector2d v_norm = v.GetNormalized();
  ASSERT_NEAR(1.0f, v_norm.GetLength(), 0.00001f);

  Vector2d v_norm2 = v_norm.GetNormalized();
  ASSERT_NEAR(1.0f, v_norm2.GetLength(), 0.00001f);
}

TEST(Vector2d, RotatedVectorHasSameLenght) {
  Vector2d v(5.0f, 7.0f);
  float l = v.GetLength();
  Vector2d v2 = v.GetRotated(DegToRad(33.0f));
  float l2 = v2.GetLength();
  ASSERT_NEAR(l, l2, 0.00001f);
}
