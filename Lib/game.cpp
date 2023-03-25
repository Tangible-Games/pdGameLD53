#include "game.h"

#include "PdSymphony/point2d.hpp"
#include "PdSymphony/segment2d.hpp"
#include "PdSymphony/vector2d.hpp"

const float Math_Pi = 3.141592653589793f;
float Math_DegToRad(float a) { return a * (Math_Pi * 0.00555555555555f); }

class Game {
 public:
  Game(PlaydateAPI* playdate) : playdate_(playdate) { onStart(); }

  int Update() {
    float cur_time = playdate_->system->getElapsedTime();
    float dt = cur_time - prev_time_;
    prev_time_ = cur_time;
    onUpdateAndDraw(dt);

    // Redraw the screen.
    return 0;
  }

 private:
  void onStart() {
    playdate_->system->logToConsole("#onStart");

    prev_time_ = playdate_->system->getElapsedTime();
    eye_ = PdSymphony::Math::Point2d(50.0f, 0.0f);
    view_dir_ = PdSymphony::Math::Vector2d(0.0f, 1.0f);
    velocity_ = 100.0f;
    rotate_velocity_deg_ = 270.0f;

    int screen_width = playdate_->display->getWidth();
    int screen_height = playdate_->display->getHeight();
    int screen_center_x = screen_width / 2;

    horizontal_fov_ = 45.0f;
    vertical_fov_ =
        ((float)screen_height / (float)screen_width) * horizontal_fov_;
    vertical_fov_tan_ = tanf(vertical_fov_);

    segments_[0] =
        PdSymphony::Math::Segment2d(PdSymphony::Math::Point2d(0.0f, 100.0f),
                                    PdSymphony::Math::Point2d(100.0f, 100.0f));
    segments_[1] =
        PdSymphony::Math::Segment2d(PdSymphony::Math::Point2d(0.0f, 25.0f),
                                    PdSymphony::Math::Point2d(0.0f, 75.0f));
    segments_[2] =
        PdSymphony::Math::Segment2d(PdSymphony::Math::Point2d(100.0f, 25.0f),
                                    PdSymphony::Math::Point2d(100.0f, 75.0f));

    wall_height_ = 100.0f;

    screen_angles_cos_ =
        (float*)playdate_->system->realloc(0, sizeof(float) * screen_width);
    screen_angles_sin_ =
        (float*)playdate_->system->realloc(0, sizeof(float) * screen_width);

    float column_angle = horizontal_fov_ / (float)screen_width;
    for (int i = 0; i < screen_width; ++i) {
      float angle = column_angle * (i - screen_center_x);
      screen_angles_cos_[i] = cosf(Math_DegToRad(angle));
      screen_angles_sin_[i] = sinf(Math_DegToRad(angle));
    }
  }

  void onUpdateAndDraw(float dt) {
    playdate_->graphics->clear(kColorWhite);

    onUpdateView(dt);

    int screen_width = playdate_->display->getWidth();
    int screen_height = playdate_->display->getHeight();

    int prev_segment_id = -1;
    int prev_y0 = 0;
    int prev_y1 = 0;
    float prev_d = 0.0f;

    for (int i = 0; i < screen_width; ++i) {
      PdSymphony::Math::Vector2d ray =
          view_dir_.GetRotated(screen_angles_cos_[i], screen_angles_sin_[i]);
      PdSymphony::Math::Segment2d ray_seg(eye_, eye_ + ray * 1000.0f);

      int segment_id = -1;
      float d = 1000.0f;
      for (int seg_i = 0; seg_i < num_segments_; ++seg_i) {
        PdSymphony::Math::Point2d intersection;
        if (ray_seg.Intersect(segments_[seg_i], 0.001f, intersection)) {
          float new_d = (intersection - eye_).GetLength();
          if (new_d < d) {
            segment_id = seg_i;
            d = new_d;
          }
        }
      }

      int y0 = 0;
      int y1 = 0;
      if (segment_id != -1) {
        float x = d * vertical_fov_tan_ * screen_angles_cos_[i];

        int wall_size_in_px = (int)((float)screen_height * (wall_height_ / x));
        y0 = (screen_height - wall_size_in_px) / 2;
        y1 = y0 + wall_size_in_px;
      }

      if (segment_id != prev_segment_id) {
        if (prev_segment_id == -1) {
          playdate_->graphics->drawLine(i, y0, i, y1, 2, kColorBlack);
        } else if (segment_id == -1) {
          playdate_->graphics->drawLine(i, prev_y0, i, prev_y1, 2, kColorBlack);
        } else {
          if (d < prev_d) {
            playdate_->graphics->drawLine(i, y0, i, y1, 2, kColorBlack);
          } else {
            playdate_->graphics->drawLine(i, prev_y0, i, prev_y1, 2,
                                          kColorBlack);
          }
        }
      } else if (segment_id != -1) {
        playdate_->graphics->drawLine(i, y0, i, y0 - 2, 1, kColorBlack);
        playdate_->graphics->drawLine(i, y1, i, y1 + 2, 1, kColorBlack);
      }

      prev_segment_id = segment_id;
      prev_y0 = y0;
      prev_y1 = y1;
      prev_d = d;
    }

    playdate_->system->drawFPS(5, 5);
  }

  void onUpdateView(float dt) {
    PDButtons buttons_current;
    PDButtons buttons_pushed;
    PDButtons buttons_released;
    playdate_->system->getButtonState(&buttons_current, &buttons_pushed,
                                      &buttons_released);

    if (buttons_current == kButtonUp) {
      eye_ = eye_ + view_dir_ * velocity_ * dt;
    } else if (buttons_current == kButtonDown) {
      eye_ = eye_ - view_dir_ * velocity_ * dt;
    }

    if (buttons_current == kButtonLeft) {
      view_dir_ =
          view_dir_.GetRotated(Math_DegToRad(-rotate_velocity_deg_ * dt));
    } else if (buttons_current == kButtonRight) {
      view_dir_ =
          view_dir_.GetRotated(Math_DegToRad(rotate_velocity_deg_ * dt));
    }
  }

  PlaydateAPI* playdate_;
  float prev_time_;

  PdSymphony::Math::Point2d eye_;
  PdSymphony::Math::Vector2d view_dir_;
  float velocity_;
  float rotate_velocity_deg_;

  float horizontal_fov_;
  float vertical_fov_;
  float vertical_fov_tan_;

  static const int num_segments_ = 3;
  PdSymphony::Math::Segment2d segments_[num_segments_];
  float wall_height_;
  float* screen_angles_cos_;
  float* screen_angles_sin_;
};

void* SetupGame(PlaydateAPI* playdate) {
  playdate->system->logToConsole("SetupGame");
  return new Game(playdate);
}

int Update(void* userdata) {
  Game* game = (Game*)userdata;
  return game->Update();
}
