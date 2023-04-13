#include "segment2d.hpp"

#include <gtest/gtest.h>

using namespace PdSymphony::Math;

TEST(Segment2d, Intersect) {
  Segment2d seg0(Point2d(0.0f, 0.0f), Point2d(0.0f, 2.0f));
  Segment2d seg1(Point2d(-1.0f, 1.0f), Point2d(1.0f, 1.0f));
  Point2d p;
  bool result = seg0.Intersect(seg1, 0.00001f, p);
  ASSERT_EQ(true, result);
  ASSERT_NEAR(0.0f, p.x, 0.001f);
  ASSERT_NEAR(1.0f, p.y, 0.001f);
}

TEST(Segment2d, IntersectFractions) {
  Segment2d seg0(Point2d(0.0f, 10.0f), Point2d(10.0f, 0.0f));

  Segment2d seg1(Point2d(0.0f, 0.0f), Point2d(100.0f, 100.0f));

  Point2d p;
  float this_seg_fraction = 0.0f;
  float seg1_fraction = 0.0f;
  bool result =
      seg0.Intersect(seg1, 0.00001f, p, this_seg_fraction, seg1_fraction);
  ASSERT_EQ(true, result);
  ASSERT_NEAR(0.5f, this_seg_fraction, 0.001f);
  ASSERT_NEAR(0.05f, seg1_fraction, 0.001f);
}
