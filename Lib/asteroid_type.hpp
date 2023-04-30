#pragma once

#include <vector>

struct AsteroidType {
  std::vector<const char*> models;
  float radius{0.0f};
  bool breaks_on_collision{false};
};
