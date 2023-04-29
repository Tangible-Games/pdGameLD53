#pragma once

#include "pd_api.h"
#include "PdSymphony/all_symphony.hpp"

using namespace PdSymphony::Math;

class Camera {
 public:
  Camera(PlaydateAPI* playdate)
      : screen_width_(playdate->display->getWidth()),
        screen_height_(playdate->display->getHeight()),
        screen_half_sizes_((float)playdate->display->getWidth() / 2.0f,
                           (float)playdate->display->getHeight() / 2.0f) {}

  void SetLookAt(const Point2d& look_at) { look_at_ = look_at; }

  Point2d ConvertToCameraSpace(const Point2d& p) const {
    return screen_half_sizes_ + (p - look_at_);
  }

 private:
  int screen_width_{0};
  int screen_height_{0};
  Point2d screen_half_sizes_;
  Point2d look_at_;
};
