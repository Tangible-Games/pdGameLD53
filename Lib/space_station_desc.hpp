#pragma once

#include <vector>

#include "PdSymphony/point2d.hpp"

using namespace PdSymphony::Math;

struct AsteroidDesc {
  Point2d pos;  // Local to station.
  float radius{0.0f};
};

struct SpaceStationDesc {
  Point2d pos;  // Global position of station.
  std::string name;
  std::string desc;
  float jump_distance{0.0f};
  std::string difficulty_str;
  int difficulty{0};
  std::vector<AsteroidDesc> asteroids;
};
