#include "pd_animations.hpp"

#include <gtest/gtest.h>

using namespace PdSymphony::Engine;

static playdate_graphics graphics;
static PlaydateAPI playdate;

static LCDBitmapTable* bitmap_table = reinterpret_cast<LCDBitmapTable*>(1);
static const int bitmap_table_num_bitmaps = 5;  // 5 frames + 1 for nullptr
static LCDBitmap* bitmap_table_bitmaps[bitmap_table_num_bitmaps] = {
    // clang-format off
  reinterpret_cast<LCDBitmap*>(1),
  reinterpret_cast<LCDBitmap*>(2),
  reinterpret_cast<LCDBitmap*>(3),
  reinterpret_cast<LCDBitmap*>(4),
  reinterpret_cast<LCDBitmap*>(5)
    // clang-format on
};

extern "C" {
LCDBitmap* getTableBitmap(LCDBitmapTable* table, int idx) {
  if (table == bitmap_table) {
    if (idx < 0 || idx >= bitmap_table_num_bitmaps) {
      return 0;
    }
    return bitmap_table_bitmaps[idx];
  }
  return 0;
}
}

TEST(PdAnimation, CalculatesNumFrames) {
  graphics.getTableBitmap = getTableBitmap;
  playdate.graphics = &graphics;

  PdAnimation animation(&playdate, bitmap_table, "animation", /* fps= */ 10.0f);

  ASSERT_EQ(5, animation.GetNumFrames());
  ASSERT_NEAR(0.5f, animation.GetLength(), 0.0001f);
}

TEST(PdAnimation, PlaysNotLooped) {
  graphics.getTableBitmap = getTableBitmap;
  playdate.graphics = &graphics;

  PdAnimation animation(&playdate, bitmap_table, "animation", /* fps= */ 50.0f);

  //    0 - 0.02 -> 1
  // 0.02 - 0.04 -> 2
  // 0.04 - 0.06 -> 3
  // 0.06 - 0.08 -> 4
  // 0.08 - 0.10 -> 5

  animation.Play(/* looped= */ false);

  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(1), animation.GetBitmap());

  animation.Update(0.019f);  // 0.019f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(1), animation.GetBitmap());

  animation.Update(0.002f);  // 0.021f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(2), animation.GetBitmap());

  animation.Update(0.04f);  // 0.061f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());

  animation.Update(0.02f);  // 0.081f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(5), animation.GetBitmap());

  animation.Update(0.1f);  // 0.181f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(5), animation.GetBitmap());
}

TEST(PdAnimation, PlaysLooped) {
  graphics.getTableBitmap = getTableBitmap;
  playdate.graphics = &graphics;

  PdAnimation animation(&playdate, bitmap_table, "animation", /* fps= */ 50.0f);

  //    0 - 0.02 -> 1
  // 0.02 - 0.04 -> 2
  // 0.04 - 0.06 -> 3
  // 0.06 - 0.08 -> 4
  // 0.08 - 0.10 -> 5

  animation.Play(/* looped= */ true);

  animation.Update(0.061f);  // 0.061f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());

  animation.Update(0.058f);  // 0.119f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(1), animation.GetBitmap());

  animation.Update(0.002f);  // 0.121f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(2), animation.GetBitmap());

  animation.Update(0.04f);  // 0.161f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());

  animation.Update(0.02f);  // 0.181f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(5), animation.GetBitmap());
}

TEST(PdAnimation, PlaysAndStops) {
  graphics.getTableBitmap = getTableBitmap;
  playdate.graphics = &graphics;

  PdAnimation animation(&playdate, bitmap_table, "animation", /* fps= */ 50.0f);

  animation.Update(0.061f);  // 0.061f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(1), animation.GetBitmap());

  animation.Play(/* looped= */ true);

  animation.Update(0.061f);  // 0.061f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());

  animation.Stop();
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(1), animation.GetBitmap());

  animation.Update(0.061f);  // 0.061f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(1), animation.GetBitmap());

  animation.Play(/* looped= */ true);

  animation.Update(0.161f);  // 0.161f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());

  animation.Stop(PdAnimation::StopMode::STAY);
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());

  PdAnimation::PlaybackParams playback_params;
  playback_params.looped = true;
  playback_params.from_start = false;
  animation.Play(playback_params);

  animation.Update(0.02f);  // 0.181f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(5), animation.GetBitmap());
}

TEST(PdAnimation, PlaysLoopedWithLoopingStartFrame) {
  graphics.getTableBitmap = getTableBitmap;
  playdate.graphics = &graphics;

  PdAnimation animation(&playdate, bitmap_table, "animation", /* fps= */ 50.0f);

  //    0 - 0.02 -> 1
  // 0.02 - 0.04 -> 2
  // 0.04 - 0.06 -> 3
  // 0.06 - 0.08 -> 4
  // 0.08 - 0.10 -> 5

  PdAnimation::PlaybackParams playback_params;
  playback_params.looped = true;
  playback_params.from_start = true;
  playback_params.looping_start_frame = 2;
  animation.Play(playback_params);

  animation.Update(0.061f);  // 0.061f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());

  animation.Update(0.02f);  // 0.081f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(5), animation.GetBitmap());

  animation.Update(0.029f);  // 0.11f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(3), animation.GetBitmap());

  animation.Update(0.02f);  // 0.13f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());
}

TEST(PdAnimation, PlaysLoopedWithLoopingCycle) {
  graphics.getTableBitmap = getTableBitmap;
  playdate.graphics = &graphics;

  PdAnimation animation(&playdate, bitmap_table, "animation", /* fps= */ 50.0f);

  // 0:    0 - 0.02 -> 1
  // 1: 0.02 - 0.04 -> 2
  // 2: 0.04 - 0.06 -> 3
  // 3: 0.06 - 0.08 -> 4
  // 4: 0.08 - 0.10 -> 5

  PdAnimation::PlaybackParams playback_params;
  playback_params.looped = true;
  playback_params.from_start = true;
  playback_params.looping_start_frame = 2;
  playback_params.looping_end_frame = 3;
  animation.Play(playback_params);

  animation.Update(0.061f);  // 0.061f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());

  animation.Update(0.02f);  // 0.081f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(3), animation.GetBitmap());

  animation.Update(0.02f);  // 0.101f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());

  animation.Update(0.02f);  // 0.121f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(3), animation.GetBitmap());

  animation.Update(0.02f);  // 0.141f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(4), animation.GetBitmap());

  animation.Stop(PdAnimation::StopMode::PLAY_TO_END);

  animation.Update(0.02f);  // 0.161f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(5), animation.GetBitmap());

  animation.Update(0.02f);  // 0.181f
  ASSERT_EQ(reinterpret_cast<LCDBitmap*>(5), animation.GetBitmap());
}
