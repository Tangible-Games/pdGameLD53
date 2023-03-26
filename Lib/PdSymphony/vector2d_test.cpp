#include "vector2d.hpp"

#include "better_assert.hpp"

const float Math_Pi = 3.141592653589793f;
float Math_DegToRad(float a) { return a * (Math_Pi * 0.00555555555555f); }

void vector2d_plus_minus() {
  PdSymphony::Math::Vector2d v1(1.0f, 2.0f);
  PdSymphony::Math::Vector2d v2(5.0f, 7.0f);

  PdSymphony::Math::Vector2d v3 = v1 + v2;
  TEST_ASSERT_EQ_F(6.0f, v3.x, 0.001f);
  TEST_ASSERT_EQ_F(9.0f, v3.y, 0.001f);

  PdSymphony::Math::Vector2d v4 = v1 - v2;
  TEST_ASSERT_EQ_F(-4.0f, v4.x, 0.001f);
  TEST_ASSERT_EQ_F(-5.0f, v4.y, 0.001f);
}

void vector2d_rotation() {
  PdSymphony::Math::Vector2d v(0.0f, 1.0f);

  PdSymphony::Math::Vector2d v1 = v.GetRotated(Math_DegToRad(90.0f));
  TEST_ASSERT_EQ_F(-1.0f, v1.x, 0.001f);
  TEST_ASSERT_EQ_F(0.0f, v1.y, 0.001f);

  PdSymphony::Math::Vector2d v2 = v.GetRotated(Math_DegToRad(-90.0f));
  TEST_ASSERT_EQ_F(1.0f, v2.x, 0.001f);
  TEST_ASSERT_EQ_F(0.0f, v2.y, 0.001f);
}

int main() {
  vector2d_plus_minus();
  vector2d_rotation();
  return 0;
}
