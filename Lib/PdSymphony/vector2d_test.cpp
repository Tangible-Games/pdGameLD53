#include "vector2d.hpp"

#include "better_assert.hpp"

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

int main() {
  vector2d_plus_minus();
  return 0;
}
