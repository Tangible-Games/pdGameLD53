#pragma once

#include <vector>

#include "PdSymphony/point2d.hpp"

using namespace PdSymphony::Math;

struct AsteroidPositionDesc {
  Point2d pos;
  float radius{0.0f};
};

struct SpaceStationDesc {
  Point2d pos;  // Local to station.
  std::string name;
  std::string desc;
  float jump_distance{0.0f};
  std::string difficulty_str;
  int difficulty{0};
  std::vector<AsteroidPositionDesc> asteroids;
};
