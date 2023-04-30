#pragma once

#include <stdint.h>

#include <array>
#include <string>

#include "PdSymphony/point2d.hpp"

struct StationArea {
  Point2d pos;  // not the same as for local game coordinates
  uint32_t seed{0};
  std::string name;
  std::array<int, 5> num_asteroids;
  float asteroids_to_base_distance{0.0f};
  float asteroids_area_distance{0.0f};
};
