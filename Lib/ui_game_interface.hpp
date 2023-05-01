#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "pd_api.h"

using namespace PdSymphony::Math;

class UiGameInterface {
 public:
  UiGameInterface(PlaydateAPI* playdate) : playdate_(playdate) {}

  void Load();
  void Update(float dt);
  void Draw();

  void SetArrow(bool is_visible, const Point2d& ship_pos, const Vector2d& dir) {
    is_arrow_visible_ = is_visible;
    ship_pos_ = ship_pos;
    arrow_dir_norm_ = dir;
  }

  void SetTimeSeconds(float time_seconds) { time_seconds_ = time_seconds; }

  void SetCrateHealthPercent(float percent) { crate_health_percent_ = percent; }

 private:
  void drawArrow();

  PlaydateAPI* playdate_;
  bool is_arrow_visible_{false};
  Point2d ship_pos_;
  Vector2d arrow_dir_norm_;
  float time_seconds_{0.0f};
  float crate_health_percent_{0.0f};
  LCDBitmapTable* arrow_bitmap_table_{nullptr};
  LCDBitmap* bottom_left_corner_{nullptr};
  LCDBitmap* bottom_right_corner_{nullptr};
  LCDBitmap* top_left_corner_{nullptr};
  LCDBitmap* top_right_corner_{nullptr};
  LCDBitmap* crate_{nullptr};
  LCDBitmapTable* clock_{nullptr};
  float running_time_{0.0f};
};
