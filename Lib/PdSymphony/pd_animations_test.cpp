#include "pd_animations.hpp"

#include <gtest/gtest.h>

using namespace PdSymphony::Engine;

static playdate_graphics graphics;
static PlaydateAPI playdate;

static LCDBitmapTable* bitmap_table = reinterpret_cast<LCDBitmapTable*>(1);
static const int bitmap_table_num_bitmaps = 6;  // 5 frames + 1 for nullptr
static LCDBitmap* bitmap_table_bitmaps[bitmap_table_num_bitmaps] = {
    reinterpret_cast<LCDBitmap*>(1), reinterpret_cast<LCDBitmap*>(2),
    reinterpret_cast<LCDBitmap*>(3), reinterpret_cast<LCDBitmap*>(4),
    reinterpret_cast<LCDBitmap*>(5), 0,
};

extern "C" {
LCDBitmap* getTableBitmap(LCDBitmapTable* table, int idx) {
  if (table == bitmap_table) {
    return bitmap_table_bitmaps[idx];
  }
  return 0;
}
}

TEST(PdAnimation, CalculatesNumFrames) {
  graphics.getTableBitmap = getTableBitmap;
  playdate.graphics = &graphics;

  PdAnimation animation(&playdate, bitmap_table, /* fps= */ 1.0f);

  ASSERT_EQ(5, animation.GetNumFrames());
}
