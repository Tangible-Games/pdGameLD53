#include "point2d.hpp"

#include "better_assert.hpp"

void point2d_plus_minus() {
  PdSymphony::Math::Point2d p1(2.0f, 4.0f);
  PdSymphony::Math::Vector2d v1(1.0f, 2.0f);
  PdSymphony::Math::Point2d p2 = p1 + v1;
  TEST_ASSERT_EQ(3.0f, p2.x);
  TEST_ASSERT_EQ(6.0f, p2.y);

  PdSymphony::Math::Point2d p3 = p1 - v1;
  TEST_ASSERT_EQ(1.0f, p3.x);
  TEST_ASSERT_EQ(2.0f, p3.y);

  PdSymphony::Math::Point2d p4(10.0f, 15.0f);
  PdSymphony::Math::Vector2d v2 = p4 - p1;
  TEST_ASSERT_EQ(8.0f, v2.x);
  TEST_ASSERT_EQ(11.0f, v2.y);
}

int main() {
  point2d_plus_minus();
  return 0;
}