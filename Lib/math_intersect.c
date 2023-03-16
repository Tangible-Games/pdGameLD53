#include "math_intersect.h"

#include <math.h>

#define Epsilon 0.00000001f

int symIntersectSegments(const Point* o1, const Point* e1, const Point* o2,
                         const Point* e2, float eps, Point* intersectionOut) {
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
    return 0;
  }
  if (t > 1.0f) {
    return 0;
  }

  float u = (a.x * v1.y - a.y * v1.x) / D;
  if (u < 0.0f) {
    return 0;
  }
  if (u > 1.0f) {
    return 0;
  }

  intersectionOut->x = o1->x + v1.x * t;
  intersectionOut->y = o1->y + v1.y * t;

  return 1;
}

void symIntersectSquareFromInside(float x, float y, float rX, float rY,
                                  float sX, float sY, int* indexXOut,
                                  int* indexYOut, float* xOut, float* yOut) {
  *indexXOut = 0;
  *indexYOut = 0;

  *xOut = 0.0f;
  *yOut = 0.0f;

  float R = sqrtf(sX * sX + sY * sY) + 1.0f;

  Point rayStart;
  rayStart.x = x;
  rayStart.y = y;

  Point rayEnd;
  rayEnd.x = rayStart.x + rX * R;
  rayEnd.y = rayStart.y + rY * R;

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
  if (symIntersectSegments(&rayStart, &rayEnd, &p3, &p2, Epsilon,
                           &intersection)) {
    // RIGHT
    *indexXOut = 1;
  } else if (symIntersectSegments(&rayStart, &rayEnd, &p1, &p2, Epsilon,
                                  &intersection)) {
    // UP
    *indexYOut = 1;
  } else if (symIntersectSegments(&rayStart, &rayEnd, &p0, &p1, Epsilon,
                                  &intersection)) {
    // LEFT
    *indexXOut = -1;
  } else if (symIntersectSegments(&rayStart, &rayEnd, &p0, &p3, Epsilon,
                                  &intersection)) {
    // DOWN
    *indexYOut = -1;
  }

  *xOut = intersection.x;
  *yOut = intersection.y;
}
