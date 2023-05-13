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
  }

  int GetNumFrames() const { return num_frames_; }

  float GetFps() const { return fps_; }

  float GetLength() const { return fps_ * num_frames_; }

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

  PlaydateAPI* playdate_{nullptr};
  LCDBitmapTable* bitmap_table_{nullptr};
  int num_frames_{-1};
  float fps_{1.0f};
};
}  // namespace Engine
}  // namespace PdSymphony
