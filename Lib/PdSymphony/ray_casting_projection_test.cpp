#include "ray_casting_projection.hpp"

#include <gtest/gtest.h>

#include "segment2d.hpp"

using namespace PdSymphony::Math;
using namespace PdSymphony::Visibility;

TEST(RayCastingProjection, Project) {
  int screen_width = 400;
  int screen_height = 240;

  RayCastingProjection proj;
  proj.SetViewport(screen_width, screen_height,
                   /* horizontal_fov_deg= */ 90.0f);

  proj.SetCamera(Point2d(0.0f, 0.0f), 6.0f, Vector2d(0.0f, 1.0f));
  Point2d result = proj.Project(Point2d(-10.0f, 10.0f), /* p_z= */ 0.0f);
  ASSERT_NEAR(-1.0f, result.x, 0.001f);
  ASSERT_NEAR(-1.0f, result.y, 0.001f);

  result = proj.Project(Vector2d(-10.0f, 10.0f).GetNormalized(),
                        Vector2d(-10.0f, 10.0f).GetLength(), /* p_z= */ 0.0f);
  ASSERT_NEAR(-1.0f, result.x, 0.001f);
  ASSERT_NEAR(-1.0f, result.y, 0.001f);

  proj.SetCamera(Point2d(0.0f, 0.0f), 6.0f, Vector2d(0.0f, 1.0f));
  result = proj.Project(Point2d(10.0f, 10.0f), /* p_z= */ 0.0f);
  ASSERT_NEAR(1.0f, result.x, 0.001f);
  ASSERT_NEAR(-1.0f, result.y, 0.001f);

  proj.SetCamera(Point2d(0.0f, 0.0f), 6.0f, Vector2d(0.0f, 1.0f));
  result = proj.Project(Point2d(0.0f, 10.0f), /* p_z= */ 12.0f);
  ASSERT_NEAR(0.0f, result.x, 0.001f);
  ASSERT_NEAR(1.0f, result.y, 0.001f);
}

TEST(RayCastingProjection, Project_OnLine) {
  Segment2d wall(Point2d(-500.0f, 100.0f), Point2d(500.0f, 100.0f));

  int screen_width = 400;
  int screen_height = 240;

  Vector2d camera_direction = Vector2d(1.0f, 1.0f).GetNormalized();

  RayCastingProjection proj;
  proj.SetViewport(screen_width, screen_height,
                   /* horizontal_fov_deg= */ 90.0f);
  proj.SetCamera(Point2d(100.0f, 50.0f), 6.0f, Vector2d(-0.903978f, 0.427579f));

  Segment2d ray_left(Point2d(0.0f, 0.0f),
                     Point2d(0.0f, 0.0f) +
                         camera_direction.GetRotated(DegToRad(70.0f)) * 500.0f);
  Point2d intersection_left;
  ray_left.Intersect(wall, 0.001f, intersection_left);
  Point2d intersection_left_p =
      proj.Project(intersection_left, /* p_z= */ 0.0f);

  Segment2d ray_center(
      Point2d(0.0f, 0.0f),
      Point2d(0.0f, 0.0f) +
          camera_direction.GetRotated(DegToRad(35.0f)) * 500.0f);
  Point2d intersection_center;
  ray_center.Intersect(wall, 0.001f, intersection_center);
  Point2d intersection_center_p =
      proj.Project(intersection_center, /* p_z= */ 0.0f);

  Segment2d ray_right(Point2d(0.0f, 0.0f),
                      Point2d(0.0f, 0.0f) +
                          camera_direction.GetRotated(DegToRad(0.0f)) * 500.0f);
  Point2d intersection_right;
  ray_right.Intersect(wall, 0.001f, intersection_right);
  Point2d intersection_right_p =
      proj.Project(intersection_right, /* p_z= */ 0.0f);

  ASSERT_TRUE(AreOnLine(intersection_left_p, intersection_center_p,
                        intersection_right_p, 0.000001f));
}
