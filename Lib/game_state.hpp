#pragma once

#include <stdint.h>

#include "PdSymphony/point2d.hpp"

struct StationArea {
  Point2d pos;  // not the same as for local game coordinates
  uint32_t seed;
};