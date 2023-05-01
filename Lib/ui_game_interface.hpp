#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "consts.hpp"
#include "pd_api.h"

using namespace PdSymphony::Math;

class UiGameInterface {
 public:
  UiGameInterface(PlaydateAPI* playdate) : playdate_(playdate) {}

  void Load();
  void Update(float dt);
  void Draw();

  void SetArrow(bool is_visible, bool is_text_visble, const Point2d& ship_pos,
                const Vector2d& dir, float distance) {
    is_arrow_visible_ = is_visible;
    is_is_arrow_text_visble_ = is_text_visble;
    ship_pos_ = ship_pos;
    arrow_dir_norm_ = dir;
    arrow_distance_ = distance;
  }

  void SetTimeVisibility(bool is_visible) { is_time_visible_ = is_visible; }

  void SetTimeSeconds(float time_seconds) { time_seconds_ = time_seconds; }

  void SetCrateHealthVisibility(bool is_visible) {
    is_crate_visible_ = is_visible;
  }

  void SetCrateHealthPercent(float percent) { crate_health_percent_ = percent; }

  void SetSpeed(float speed) { speed_ = speed; }

  void SetMovingTooFastText(bool show) {
    if (show) {
      moving_too_fast_time_ = kUiMovingTooFastTimeout;
      moving_too_fast_force_hidden_ = false;
    } else {
      moving_too_fast_force_hidden_ = true;
    }
  }

  void SetReadyToJump(bool show) { ready_to_jump_ = show; }

 private:
  void drawArrow();

  PlaydateAPI* playdate_;
  bool is_arrow_visible_{false};
  bool is_is_arrow_text_visble_{false};
  Point2d ship_pos_;
  Vector2d arrow_dir_norm_;
  float arrow_distance_{0.0f};
  bool is_time_visible_{false};
  float time_seconds_{0.0f};
  bool is_crate_visible_{false};
  float crate_health_percent_{0.0f};
  float speed_{0.0f};
  float moving_too_fast_time_{0.0f};
  bool moving_too_fast_force_hidden_{false};
  bool ready_to_jump_{false};
  LCDBitmapTable* arrow_bitmap_table_{nullptr};
  LCDBitmap* bottom_left_corner_{nullptr};
  LCDBitmap* bottom_right_corner_{nullptr};
  LCDBitmap* top_left_corner_{nullptr};
  LCDBitmap* top_right_corner_{nullptr};
  LCDBitmap* crate_{nullptr};
  LCDBitmapTable* clock_{nullptr};
  float running_time_{0.0f};
  const int text_glyph_width_{10};
  const int text_glyph_height_{12};
};
