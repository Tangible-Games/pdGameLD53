#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "pd_api.h"

using namespace PdSymphony::Math;

inline void GetBitmapSizes(PlaydateAPI* playdate, LCDBitmap* bitmap,
                           int& width_out, int& height_out) {
  int bitmap_row_bytes = 0;
  uint8_t* bitmap_mask = 0;
  uint8_t* bitmap_data = 0;
  playdate->graphics->getBitmapData(bitmap, &width_out, &height_out,
                                    &bitmap_row_bytes, &bitmap_mask,
                                    &bitmap_data);
}

inline void DrawBitmapCentered(PlaydateAPI* playdate, LCDBitmap* bitmap,
                               const Point2d& center) {
  int bitmap_width = 0;
  int bitmap_height = 0;
  int bitmap_row_bytes = 0;
  uint8_t* bitmap_mask = 0;
  uint8_t* bitmap_data = 0;
  playdate->graphics->getBitmapData(bitmap, &bitmap_width, &bitmap_height,
                                    &bitmap_row_bytes, &bitmap_mask,
                                    &bitmap_data);

  int x = (int)center.x - bitmap_width / 2;
  int y = (int)center.y - bitmap_height / 2;
  playdate->graphics->drawBitmap(bitmap, x, y, kBitmapUnflipped);
}
