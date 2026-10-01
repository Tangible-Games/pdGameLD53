#include "hash.hpp"

#include <gtest/gtest.h>

using namespace PdSymphony::Hash;

static uint32_t HashStr(const char* str, size_t length,
                        uint32_t hash_start = 0) {
  return HashLy(reinterpret_cast<const unsigned char*>(str), length,
                hash_start);
}

TEST(HashLy, DependsOnAllBytes) {
  // Same length and same first byte.
  ASSERT_NE(HashStr("Central Station", 15), HashStr("Central Statiom", 15));
  ASSERT_NE(HashStr("ab", 2), HashStr("ac", 2));
}

TEST(HashLy, MatchesReferenceValues) {
  // result = result * 1664525 + byte + 1013904223, for each byte.
  ASSERT_EQ(1013904320u, HashStr("a", 1));
  ASSERT_EQ(1013904320u * 1664525u + 'b' + 1013904223u, HashStr("ab", 2));
}

TEST(HashLy, ContinuesFromHashStart) {
  ASSERT_EQ(HashStr("ab", 2), HashStr("b", 1, HashStr("a", 1)));
}
