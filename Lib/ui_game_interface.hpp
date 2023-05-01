#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "pd_api.h"

class UiGameInterface {
 public:
  UiGameInterface(PlaydateAPI* playdate) : playdate_(playdate) {}

  void Load();
  void Update(float dt);
  void Draw();

  void SetTimeSeconds(float time_seconds) { time_seconds_ = time_seconds; }

  void SetCrateHealthPercent(float percent) { crate_health_percent_ = percent; }

 private:
  PlaydateAPI* playdate_;
  float time_seconds_{0.0f};
  float crate_health_percent_{0.0f};
  LCDBitmap* bottom_left_corner_{nullptr};
  LCDBitmap* bottom_right_corner_{nullptr};
  LCDBitmap* top_left_corner_{nullptr};
  LCDBitmap* top_right_corner_{nullptr};
  LCDBitmap* crate_{nullptr};
  LCDBitmapTable* clock_{nullptr};
  float running_time_{0.0f};
};
