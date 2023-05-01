#include "aa_rect2d.hpp"

#include <gtest/gtest.h>

using namespace PdSymphony::Math;

TEST(AARect2d, Corners) {
  AARect2d rect(Point2d(10.0f, 15.0f),
                /* new_half_size= */ Vector2d(2.0f, 3.0f));
  ASSERT_NEAR(8.0f, rect.BottomLeft().x, 0.001f);
  ASSERT_NEAR(12.0f, rect.BottomLeft().y, 0.001f);
  ASSERT_NEAR(12.0f, rect.TopRight().x, 0.001f);
  ASSERT_NEAR(18.0f, rect.TopRight().y, 0.001f);
}

TEST(AARect2d, IsPointInside) {
  AARect2d rect(Point2d(10.0f, 15.0f), Vector2d(2.0f, 3.0f));
  ASSERT_TRUE(rect.IsPointInside(Point2d(10.0f, 15.0f)));
  ASSERT_FALSE(rect.IsPointInside(Point2d(19.0f, 15.0f)));
  ASSERT_FALSE(rect.IsPointInside(Point2d(7.0f, 15.0f)));
  ASSERT_TRUE(rect.IsPointInside(Point2d(9.0f, 15.0f)));
  ASSERT_FALSE(rect.IsPointInside(Point2d(9.0f, 11.0f)));
  ASSERT_FALSE(rect.IsPointInside(Point2d(9.0f, 19.0f)));
  // border
  ASSERT_FALSE(rect.IsPointInside(Point2d(8.0f, 15.0f)));
  ASSERT_FALSE(rect.IsPointInside(Point2d(12.0f, 15.0f)));
  ASSERT_FALSE(rect.IsPointInside(Point2d(10.0f, 12.0f)));
  ASSERT_FALSE(rect.IsPointInside(Point2d(10.0f, 18.0f)));
}

TEST(AARect2d, IsPointOnLeftBorder) {
  AARect2d rect(Point2d(10.0f, 15.0f), Vector2d(2.0f, 3.0f));
  ASSERT_TRUE(rect.IsPointOnLeftBorder(Point2d(8.0f, 15.0f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnLeftBorder(Point2d(8.1f, 15.0f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnLeftBorder(Point2d(8.0f, 18.1f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnLeftBorder(Point2d(8.0f, 11.9f), 0.0001f));
}

TEST(AARect2d, IsPointOnRightBorder) {
  AARect2d rect(Point2d(10.0f, 15.0f), Vector2d(2.0f, 3.0f));
  ASSERT_TRUE(rect.IsPointOnRightBorder(Point2d(12.0f, 15.0f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnRightBorder(Point2d(12.1f, 15.0f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnRightBorder(Point2d(12.0f, 18.1f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnRightBorder(Point2d(12.0f, 11.9f), 0.0001f));
}

TEST(AARect2d, IsPointOnTopBorder) {
  AARect2d rect(Point2d(10.0f, 15.0f), Vector2d(2.0f, 3.0f));
  ASSERT_TRUE(rect.IsPointOnTopBorder(Point2d(10.0f, 18.0f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnTopBorder(Point2d(10.0f, 18.1f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnTopBorder(Point2d(7.9f, 18.0f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnTopBorder(Point2d(12.1f, 18.0f), 0.0001f));
}

TEST(AARect2d, IsPointOnBottomBorder) {
  AARect2d rect(Point2d(10.0f, 15.0f), Vector2d(2.0f, 3.0f));
  ASSERT_TRUE(rect.IsPointOnBottomBorder(Point2d(10.0f, 12.0f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnBottomBorder(Point2d(10.0f, 12.1f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnBottomBorder(Point2d(7.9f, 12.0f), 0.0001f));
  ASSERT_FALSE(rect.IsPointOnBottomBorder(Point2d(12.1f, 12.0f), 0.0001f));
}

TEST(AARect2d, IntersectRayFromInside) {
  AARect2d rect(Point2d(10.0f, 15.0f),
                /* new_half_size= */ Vector2d(2.0f, 3.0f));

  AARect2d::FromInsideIntersection intersection;

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 15.0f),
      /* ray_dir_norm= */ Vector2d(2.0f, 2.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(12.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(17.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(1, intersection.dx);
  ASSERT_EQ(0, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 15.0f),
      /* ray_dir_norm= */ Vector2d(2.0f, 1.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(12.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(16.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(1, intersection.dx);
  ASSERT_EQ(0, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 17.0f),
      /* ray_dir_norm= */ Vector2d(1.0f, 1.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(11.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(18.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(0, intersection.dx);
  ASSERT_EQ(1, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 13.0f),
      /* ray_dir_norm= */ Vector2d(1.0f, -1.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(11.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(12.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(0, intersection.dx);
  ASSERT_EQ(-1, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 15.0f),
      /* ray_dir_norm= */ Vector2d(-2.0f, 2.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(8.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(17.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(-1, intersection.dx);
  ASSERT_EQ(0, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 15.0f),
      /* ray_dir_norm= */ Vector2d(-2.0f, 1.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(8.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(16.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(-1, intersection.dx);
  ASSERT_EQ(0, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 17.0f),
      /* ray_dir_norm= */ Vector2d(-1.0f, 1.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(9.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(18.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(0, intersection.dx);
  ASSERT_EQ(1, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 13.0f),
      /* ray_dir_norm= */ Vector2d(-1.0f, -1.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(9.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(12.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(0, intersection.dx);
  ASSERT_EQ(-1, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 15.0f),
      /* ray_dir_norm= */ Vector2d(1.0f, 3.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(11.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(18.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(0, intersection.dx);
  ASSERT_EQ(1, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 15.0f),
      /* ray_dir_norm= */ Vector2d(2.0f, 3.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(12.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(18.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(0, intersection.dx);
  ASSERT_EQ(1, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 15.0f),
      /* ray_dir_norm= */ Vector2d(1.0f, 0.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(12.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(15.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(1, intersection.dx);
  ASSERT_EQ(0, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 15.0f),
      /* ray_dir_norm= */ Vector2d(-1.0f, 0.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(8.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(15.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(-1, intersection.dx);
  ASSERT_EQ(0, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 15.0f),
      /* ray_dir_norm= */ Vector2d(0.0f, 1.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(10.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(18.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(0, intersection.dx);
  ASSERT_EQ(1, intersection.dy);

  rect.IntersectRayFromInside(
      /* ray_start= */ Point2d(10.0f, 15.0f),
      /* ray_dir_norm= */ Vector2d(0.0f, -1.0f).GetNormalized(), intersection);
  ASSERT_TRUE(intersection.has_intersection);
  ASSERT_NEAR(10.0f, intersection.p.x, 0.0001f);
  ASSERT_NEAR(12.0f, intersection.p.y, 0.0001f);
  ASSERT_EQ(0, intersection.dx);
  ASSERT_EQ(-1, intersection.dy);
}
