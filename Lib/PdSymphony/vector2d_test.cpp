#include "vector2d.hpp"

#include "better_assert.hpp"

const float Math_Pi = 3.141592653589793f;
float Math_DegToRad(float a) { return a * (Math_Pi * 0.00555555555555f); }

void vector2d_plus_minus() {
  PdSymphony::Math::Vector2d v1(1.0f, 2.0f);
  PdSymphony::Math::Vector2d v2(5.0f, 7.0f);

  PdSymphony::Math::Vector2d v3 = v1 + v2;
  TEST_ASSERT_EQ(6.0f, v3.x);
  TEST_ASSERT_EQ(9.0f, v3.y);

  PdSymphony::Math::Vector2d v4 = v1 - v2;
  TEST_ASSERT_EQ(-4.0f, v4.x);
  TEST_ASSERT_EQ(-5.0f, v4.y);
}

void vector2d_rotation() {
  PdSymphony::Math::Vector2d v(0.0f, 1.0f);

  PdSymphony::Math::Vector2d v1 = v.GetRotated(Math_DegToRad(90.0f));
  TEST_ASSERT_EQ(-1.0f, v1.x);
  TEST_ASSERT_EQ(0.0f, v1.y);

  PdSymphony::Math::Vector2d v2 = v.GetRotated(Math_DegToRad(-90.0f));
  TEST_ASSERT_EQ(1.0f, v1.x);
  TEST_ASSERT_EQ(0.0f, v1.y);
}

int main() {
  vector2d_plus_minus();
  vector2d_rotation();
  return 0;
}
