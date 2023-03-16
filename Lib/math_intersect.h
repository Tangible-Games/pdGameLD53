#ifndef __MATH_INTERSECT_H_
#define __MATH_INTERSECT_H_

typedef struct Point {
  float x;
  float y;
} Point;

int symIntersectSegments(const Point* o1, const Point* e1, const Point* o2,
                         const Point* e2, float eps, Point* intersectionOut);

void symIntersectSquareFromInside(float x, float y, float rX, float rY,
                                  float sX, float sY, int* indexXOut,
                                  int* indexYOut, float* xOut, float* yOut);

#endif
