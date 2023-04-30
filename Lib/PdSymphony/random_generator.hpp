#pragma once

namespace PdSymphony {
namespace Random {
class RandomGenerator {
 public:
  RandomGenerator() {}

  void SetSeed(long seed) {
    current_value_ = seed;
    NextValue();
  }

  unsigned int NextValue() {
    current_value_ = 214013 * current_value_ + 2531011;
    return (unsigned int)(current_value_ >> 16) & 0x7FFF;
  }

  unsigned int MaxValue() const { return 0x7FFF - 1; }

 private:
  long current_value_{0};
};
}  // namespace Random
}  // namespace PdSymphony
