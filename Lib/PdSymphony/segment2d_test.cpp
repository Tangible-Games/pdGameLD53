#include "segment2d.hpp"

#include "better_assert.hpp"

void Segment2d_intersect() {
  {
    PdSymphony::Math::Segment2d seg0(PdSymphony::Math::Point2d(0.0f, 0.0f), PdSymphony::Math::Point2d(0.0f, 2.0f));
    PdSymphony::Math::Segment2d seg1(PdSymphony::Math::Point2d(-1.0f, 1.0f), PdSymphony::Math::Point2d(1.0f, 1.0f));
    PdSymphony::Math::Point2d p;
    bool result = seg0.Intersect(seg1, 0.00001f, p);
    TEST_ASSERT_EQ(true, result);
    TEST_ASSERT_EQ(0.0f, p.x);
    TEST_ASSERT_EQ(1.0f, p.y);
  }

}

int main() {
  Segment2d_intersect();
  return 0;
}
