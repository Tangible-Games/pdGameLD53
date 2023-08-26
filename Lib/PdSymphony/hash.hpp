#pragma once

#include <stddef.h>

namespace PdSymphony {
namespace Hash {
inline uint32_t HashLy(const unsigned char* str, size_t length,
                       uint32_t hash_start = 0) {
  uint32_t result = hash_start;
  for (size_t i = 0; i < length; ++i) {
    result = (result * 1664525) + (*str) + 1013904223;
  }
  return result;
}
}  // namespace Hash
}  // namespace PdSymphony
