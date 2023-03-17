#include "math_intersect.h"

#include <math.h>

#define Epsilon 0.00000001f

int symIntersectSegments(const Point* o1, const Point* e1, const Point* o2,
                         const Point* e2, float eps, Point* intersection_out) {
  Point v1;
  v1.x = e1->x - o1->x;
  v1.y = e1->y - o1->y;

  Point v2;
  v2.x = e2->x - o2->x;
  v2.y = e2->y - o2->y;

  float D = v1.x * v2.y - v1.y * v2.x;
  if (fabsf(D) < eps) {
    return 0;
  }

  Point a;
  a.x = o2->x - o1->x;
  a.y = o2->y - o1->y;

  float t = (a.x * v2.y - a.y * v2.x) / D;
  if (t < 0.0f) {
    return -1;
  }
  if (t > 1.0f) {
    return -1;
  }

  float u = (a.x * v1.y - a.y * v1.x) / D;
  if (u < 0.0f) {
    return -1;
  }
  if (u > 1.0f) {
    return -1;
  }

  intersection_out->x = o1->x + v1.x * t;
  intersection_out->y = o1->y + v1.y * t;

  return 0;
}

void symIntersectSquareFromInside(float x, float y, float rX, float rY,
                                  float sX, float sY, int* d_i, int* d_j,
                                  float* x_out, float* y_out) {
  *d_i = 0;
  *d_j = 0;

  *x_out = 0.0f;
  *y_out = 0.0f;

  float R = sqrtf(sX * sX + sY * sY) * 1.5f;

  Point ray_start;
  ray_start.x = x;
  ray_start.y = y;

  Point ray_end;
  ray_end.x = ray_start.x + rX * R;
  ray_end.y = ray_start.y + rY * R;

  // p1--p2
  // |   |
  // p0--p3

  Point p0;
  p0.x = 0.0f;
  p0.y = 0.0f;

  Point p1;
  p0.x = 0.0f;
  p0.y = sY;

  Point p2;
  p0.x = sX;
  p0.y = sY;

  Point p3;
  p0.x = sX;
  p0.y = 0.0f;

  Point intersection;
  if (symIntersectSegments(&ray_start, &ray_end, &p3, &p2, Epsilon,
                           &intersection)) {
    // RIGHT
    *d_i = 1;
  } else if (symIntersectSegments(&ray_start, &ray_end, &p1, &p2, Epsilon,
                                  &intersection)) {
    // UP
    *d_j = 1;
  } else if (symIntersectSegments(&ray_start, &ray_end, &p0, &p1, Epsilon,
                                  &intersection)) {
    // LEFT
    *d_i = -1;
  } else if (symIntersectSegments(&ray_start, &ray_end, &p0, &p3, Epsilon,
                                  &intersection)) {
    // DOWN
    *d_j = -1;
  }

  *x_out = intersection.x;
  *y_out = intersection.y;
}
