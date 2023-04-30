#include "static_random_generator.hpp"

RandomGenerator& StaticRandomGenerator::get() {
  static RandomGenerator rg;
  return rg;
}
