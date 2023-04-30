#pragma once

#include <vector>

#include "pd_api.h"

struct AsteroidType {
  std::vector<const char*> models;
  std::vector<LCDBitmap*> bitmaps;
  float radius{0.0f};
  bool breaks_on_collision{false};
};
