#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "pd_api.h"

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

inline LCDBitmap* SelectFrame(PlaydateAPI* playdate,
                              LCDBitmapTable* bitmap_table,
                              float animation_length, int num_frames,
                              float running_time) {
  float frame_time = animation_length / (float)num_frames;
  if (running_time > animation_length) {
    running_time = animation_length;
  }
  int index = (int)(running_time / frame_time);
  if (index > num_frames - 1) {
    index = num_frames - 1;
  }
  return playdate->graphics->getTableBitmap(bitmap_table, index);
}

inline LCDBitmap* SelectFrameLooped(PlaydateAPI* playdate,
                                    LCDBitmapTable* bitmap_table,
                                    float animation_length, int num_frames,
                                    float running_time) {
  float frame_time = animation_length / (float)num_frames;
  while (running_time > animation_length) {
    running_time -= animation_length;
  }
  int index = (int)(running_time / frame_time);
  if (index > num_frames - 1) {
    index = num_frames - 1;
  }
  return playdate->graphics->getTableBitmap(bitmap_table, index);
}

inline LCDBitmap* SelectFrameFromSequence(PlaydateAPI* playdate,
                                          LCDBitmapTable* bitmap_table,
                                          float animation_length,
                                          int num_frames, int seq_start,
                                          int seq_length, float running_time) {
  float frame_time = animation_length / (float)num_frames;
  float loop_time = frame_time * seq_length;
  if (running_time > loop_time) {
    running_time = loop_time;
  }
  int index = (int)(running_time / frame_time);
  if (index > num_frames - 1) {
    index = num_frames - 1;
  }
  return playdate->graphics->getTableBitmap(bitmap_table, seq_start + index);
}

inline LCDBitmap* SelectFrameFromSequenceLooped(
    PlaydateAPI* playdate, LCDBitmapTable* bitmap_table, float animation_length,
    int num_frames, int seq_start, int seq_length, float running_time) {
  float frame_time = animation_length / (float)num_frames;
  float loop_time = frame_time * seq_length;
  while (running_time > loop_time) {
    running_time -= loop_time;
  }
  int index = (int)(running_time / frame_time);
  if (index > num_frames - 1) {
    index = num_frames - 1;
  }
  return playdate->graphics->getTableBitmap(bitmap_table, seq_start + index);
}
