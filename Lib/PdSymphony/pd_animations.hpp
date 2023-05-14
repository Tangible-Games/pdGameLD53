#pragma once

#include "pd_api.h"

namespace PdSymphony {
namespace Engine {
class PdAnimation {
 public:
  PdAnimation() {}

  PdAnimation(PlaydateAPI* playdate, LCDBitmapTable* bitmap_table, float fps,
              int num_frames = -1) {
    Create(playdate, bitmap_table, fps, num_frames);
  }

  void Create(PlaydateAPI* playdate, LCDBitmapTable* bitmap_table, float fps,
              int num_frames = -1) {
    playdate_ = playdate;
    bitmap_table_ = bitmap_table;
    num_frames_ = num_frames;
    fps_ = fps;

    if (num_frames_ == -1) {
      updateNumFrames();
    }

    is_playing_ = false;
    looped_ = false;
    running_time_ = 0.0f;
  }

  int GetNumFrames() const { return num_frames_; }

  float GetFps() const { return fps_; }

  float GetLength() const { return ((float)num_frames_) / fps_; }

  void Play(bool looped, bool from_start = true) {
    is_playing_ = true;
    looped_ = looped;

    if (from_start) {
      running_time_ = 0.0f;
    }
  }

  void Stop(bool jump_to_start = true) {
    is_playing_ = false;

    if (jump_to_start) {
      running_time_ = 0.0f;
    }
  }

  void Update(float dt) {
    if (!is_playing_) {
      return;
    }

    running_time_ += dt;
    if (!looped_) {
      if (running_time_ > GetLength()) {
        running_time_ = GetLength();
      }
    }
  }

  LCDBitmap* GetBitmap() {
    return playdate_->graphics->getTableBitmap(bitmap_table_,
                                               getCurrentFrame());
  }

 private:
  void updateNumFrames() {
    while (true) {
      ++num_frames_;
      LCDBitmap* bitmap =
          playdate_->graphics->getTableBitmap(bitmap_table_, num_frames_);
      if (bitmap == nullptr) {
        break;
      }
    }
  }

  int getCurrentFrame() const {
    float frame_length = 1.0f / fps_;
    int frame_index = 0;
    if (looped_) {
    } else {
      frame_index = floorf(running_time_ / frame_length);
      if (frame_index >= num_frames_) {
        frame_index = num_frames_ - 1;
      }
    }
    return frame_index;
  }

  PlaydateAPI* playdate_{nullptr};
  LCDBitmapTable* bitmap_table_{nullptr};
  int num_frames_{-1};
  float fps_{1.0f};
  bool is_playing_{false};
  bool looped_{false};
  float running_time_{0.0f};
};
}  // namespace Engine
}  // namespace PdSymphony
