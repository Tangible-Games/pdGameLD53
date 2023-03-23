#include "vector2d.hpp"

#include "better_assert.hpp"

void vector2d_sum() {
  PdSymphony::Math::Vector2d v1(1.0f, 2.0f);
  PdSymphony::Math::Vector2d v2(5.0f, 7.0f);
  PdSymphony::Math::Vector2d v3 = v1 + v2;
  TEST_ASSERT_EQ(6.0f, v3.x);
  TEST_ASSERT_EQ(19.0f, v3.y);
}

int main() {
  vector2d_sum();
  return 0;
}
