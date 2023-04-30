#pragma once

#include "PdSymphony/all_symphony.hpp"

using namespace PdSymphony::Random;

class StaticRandomGenerator {
 public:
  static RandomGenerator& get();
};
