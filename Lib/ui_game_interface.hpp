#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "pd_api.h"

class UiGameInterface {
 public:
  UiGameInterface(PlaydateAPI* playdate) : playdate_(playdate) {}

  void Load();
  void Update(float dt);
  void Draw();

 private:
  PlaydateAPI* playdate_;
  LCDBitmap* bottom_left_corner_{nullptr};
  LCDBitmap* bottom_right_corner_{nullptr};
  LCDBitmap* top_left_corner_{nullptr};
  LCDBitmap* top_right_corner_{nullptr};
  LCDBitmap* crate_{nullptr};
  LCDBitmapTable* clock_{nullptr};
  float running_time_{0.0f};
};
