#pragma once

#include "pd_api.h"

namespace PdSymphony {
namespace Engine {
class PdAnimation {
 public:
  struct PlaybackParams {
    bool looped{false};
    bool from_start{true};
    int looping_start_frame{0};
    int looping_end_frame{-1};
  };

  enum class StopMode { JUMP_TO_START, STAY, PLAY_TO_END };

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

    playback_state_ = PlaybackState::IDLE;
    playback_params_ = PlaybackParams();
    time_in_animation_ = 0.0f;
  }

  int GetNumFrames() const { return num_frames_; }

  float GetFps() const { return fps_; }

  float GetLength() const { return ((float)num_frames_) / fps_; }

  void Play(bool looped) {
    PlaybackParams params;
    params.looped = looped;
    Play(params);
  }

  void Play(const PlaybackParams& playback_params) {
    playback_params_ = playback_params;

    if (playback_params_.looped) {
      if (playback_params_.looping_end_frame == -1) {
        playback_params_.looping_end_frame = num_frames_ - 1;
      }

      float frame_length = 1.0f / fps_;

      looping_start_time_ = frame_length * playback_params_.looping_start_frame;
      looping_end_time_ =
          frame_length * (playback_params_.looping_end_frame + 1);
    }

    playback_state_ = PlaybackState::PLAY;

    if (playback_params_.from_start) {
      time_in_animation_ = 0.0f;
    }
  }

  void Stop(StopMode stop_mode = StopMode::JUMP_TO_START) {
    if (playback_state_ != PlaybackState::PLAY) {
      return;
    }

    switch (stop_mode) {
      case StopMode::JUMP_TO_START:
        time_in_animation_ = 0.0f;
        current_frame_index_ = 0;
        playback_state_ = PlaybackState::IDLE;
        break;

      case StopMode::STAY:
        playback_state_ = PlaybackState::IDLE;
        break;

      case StopMode::PLAY_TO_END:
        playback_state_ = PlaybackState::STOP;
        break;
    }
  }

  bool IsIdle() const { return (playback_state_ == PlaybackState::IDLE); }

  void Update(float dt) {
    float animation_length = GetLength();

    switch (playback_state_) {
      case PlaybackState::IDLE:
        break;

      case PlaybackState::PLAY:
        if (!playback_params_.looped) {
          time_in_animation_ += dt;
          if (time_in_animation_ > animation_length) {
            time_in_animation_ = animation_length;
            playback_state_ = PlaybackState::IDLE;

            current_frame_index_ = num_frames_ - 1;
          } else {
            float frame_length = 1.0f / fps_;
            current_frame_index_ = floorf(time_in_animation_ / frame_length);
          }
        } else {
          time_in_animation_ += dt;
          if (time_in_animation_ > looping_end_time_) {
            float loop_length = looping_end_time_ - looping_start_time_;

            float t = time_in_animation_ - looping_end_time_;
            time_in_animation_ =
                looping_start_time_ + t - floorf(t / loop_length) * loop_length;
          }

          float frame_length = 1.0f / fps_;
          current_frame_index_ = floorf(time_in_animation_ / frame_length);
        }
        break;

      case PlaybackState::STOP:
        time_in_animation_ += dt;
        if (time_in_animation_ > animation_length) {
          time_in_animation_ = animation_length;
          playback_state_ = PlaybackState::IDLE;

          current_frame_index_ = num_frames_ - 1;
        } else {
          float frame_length = 1.0f / fps_;
          current_frame_index_ = floorf(time_in_animation_ / frame_length);
        }
        break;
    }
  }

  LCDBitmap* GetBitmap() {
    return playdate_->graphics->getTableBitmap(bitmap_table_,
                                               current_frame_index_);
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

  enum class PlaybackState { IDLE, PLAY, STOP };

  PlaydateAPI* playdate_{nullptr};
  LCDBitmapTable* bitmap_table_{nullptr};
  int num_frames_{-1};
  float fps_{1.0f};
  PlaybackState playback_state_{PlaybackState::IDLE};
  PlaybackParams playback_params_;
  float looping_start_time_{0.0f};
  float looping_end_time_{0.0f};
  float time_in_animation_{0.0f};
  int current_frame_index_{0};
};
}  // namespace Engine
}  // namespace PdSymphony
