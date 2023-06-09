#include "ui_game_interface.hpp"

#include <iomanip>
#include <sstream>

#include "fonts.hpp"
#include "pd_helpers.hpp"

void UiGameInterface::Load() {
  const char* error = nullptr;

  LCDBitmapTable* bitmap_table =
      playdate_->graphics->loadBitmapTable("data/triangle_3.gif", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load arrow, error: %s", error);
  }
  arrow_bitmap_animation_.Create(playdate_, bitmap_table, "data/triangle_3.gif",
                                 kUiArrowAnimationFps);

  bottom_left_corner_ =
      playdate_->graphics->loadBitmap("data/bottom_left.png", &error);
  if (error) {
    playdate_->system->logToConsole(
        "Failed to load bottom left corner, error: %s", error);
  }

  bottom_right_corner_ =
      playdate_->graphics->loadBitmap("data/bottom_right.png", &error);
  if (error) {
    playdate_->system->logToConsole(
        "Failed to load bottom right corner, error: %s", error);
  }

  top_left_corner_ =
      playdate_->graphics->loadBitmap("data/top_left.png", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load top left corner, error: %s",
                                    error);
  }

  top_right_corner_ =
      playdate_->graphics->loadBitmap("data/top_right.png", &error);
  if (error) {
    playdate_->system->logToConsole(
        "Failed to load top right corner, error: %s", error);
  }

  crate_ = playdate_->graphics->loadBitmap("data/crate.png", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load crate, error: %s", error);
  }

  bitmap_table = playdate_->graphics->loadBitmapTable("data/clock.gif", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load clock, error: %s", error);
  }
  clock_.Create(playdate_, bitmap_table, "data/clock.gif",
                kUiClockAnimationFps);
}

void UiGameInterface::Update(float dt) {
  running_time_ += dt;

  if (moving_too_fast_time_ > 0.0f) {
    moving_too_fast_time_ -= dt;
    if (moving_too_fast_time_ < 0.0f) {
      moving_too_fast_time_ = 0.0f;
    }
  }

  arrow_bitmap_animation_.Update(dt);
  clock_.Update(dt);
}

void UiGameInterface::Draw() {
  drawArrow();

  int screen_width = playdate_->display->getWidth();
  int screen_height = playdate_->display->getHeight();
  int bitmap_width = 0;
  int bitmap_height = 0;

  playdate_->graphics->drawBitmap(top_left_corner_, 0, 0, kBitmapUnflipped);

  GetBitmapSizes(playdate_, top_right_corner_, bitmap_width, bitmap_height);
  playdate_->graphics->drawBitmap(
      top_right_corner_, screen_width - bitmap_width, 0, kBitmapUnflipped);

  GetBitmapSizes(playdate_, bottom_left_corner_, bitmap_width, bitmap_height);
  playdate_->graphics->drawBitmap(
      bottom_left_corner_, 0, screen_height - bitmap_height, kBitmapUnflipped);

  GetBitmapSizes(playdate_, bottom_right_corner_, bitmap_width, bitmap_height);
  playdate_->graphics->drawBitmap(
      bottom_right_corner_, screen_width - bitmap_width,
      screen_height - bitmap_height, kBitmapUnflipped);

  int crate_width = 0;
  int crate_height = 0;
  if (is_crate_visible_) {
    GetBitmapSizes(playdate_, crate_, crate_width, crate_height);
    playdate_->graphics->drawBitmap(crate_, screen_width - crate_width - 15,
                                    screen_height - crate_height - 15,
                                    kBitmapUnflipped);
  }

  LCDBitmap* bitmap = nullptr;

  int clock_width = 0;
  int clock_height = 0;
  if (is_time_visible_) {
    bitmap = clock_.GetBitmap();
    GetBitmapSizes(playdate_, bitmap, clock_width, clock_height);
    playdate_->graphics->drawBitmap(
        bitmap, 15, screen_height - clock_height - 15, kBitmapUnflipped);
  }

  playdate_->graphics->setFont(
      Fonts::instance().use(FontName::kFontBoldOutlined));

  std::string text;

  if (is_time_visible_) {
    int seconds = (int)time_seconds_;
    int minutes = seconds / 60;
    seconds = seconds % 60;

    std::ostringstream ss;
    ss << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2)
       << std::setfill('0') << seconds;

    playdate_->graphics->drawText(ss.str().data(), ss.str().size(),
                                  kASCIIEncoding, 15 + clock_width + 5,
                                  screen_height - clock_height - 13);
  }

  if (is_crate_visible_) {
    text = std::to_string((int)crate_health_percent_) + "%";
    playdate_->graphics->drawText(
        text.data(), text.size(), kASCIIEncoding,
        screen_width - crate_width - 25 - (int)text.size() * text_glyph_width_,
        screen_height - crate_height - 13);
  }

  if (kUiDrawSpeed) {
    text = std::to_string((int)speed_);
    playdate_->graphics->drawText(
        text.data(), text.size(), kASCIIEncoding,
        (screen_width - (int)text.size() * text_glyph_width_) / 2,
        screen_height - text_glyph_height_ - 13);
  }

  if (!moving_too_fast_force_hidden_ && moving_too_fast_time_ > 0.0f) {
    text = "Moving too fast. Decrease speed to dock.";
    playdate_->graphics->drawText(
        text.data(), text.size(), kASCIIEncoding,
        (screen_width - (int)text.size() * text_glyph_width_) / 2 + 55, 35);
  }

  if (ready_to_jump_) {
    text = "Ready to jump. Use Crank to jump.";
    playdate_->graphics->drawText(
        text.data(), text.size(), kASCIIEncoding,
        (screen_width - (int)text.size() * text_glyph_width_) / 2 + 55, 35);
  }
}

void UiGameInterface::drawArrow() {
  int screen_width = playdate_->display->getWidth();
  int screen_height = playdate_->display->getHeight();
  AARect2d screen_rect(
      Point2d((float)screen_width / 2.0f, (float)screen_height / 2.0f),
      Vector2d((float)screen_width / 2.0f, (float)screen_height / 2.0f));

  if (is_arrow_visible_) {
    AARect2d::FromInsideIntersection intersection;
    screen_rect.IntersectRayFromInside(ship_pos_, arrow_dir_norm_,
                                       intersection);

    LCDBitmap* bitmap = arrow_bitmap_animation_.GetBitmap();

    int bitmap_width = 0;
    int bitmap_height = 0;
    GetBitmapSizes(playdate_, bitmap, bitmap_width, bitmap_height);

    std::string text = std::to_string((int)arrow_distance_);
    int text_width = (int)text.size() * text_glyph_width_;

    Point2d sprite_pos = intersection.p;
    int text_x = 0;
    int text_y = 0;
    float angle = 0.0f;
    if (intersection.dx == 1) {
      sprite_pos.x = sprite_pos.x - (float)bitmap_width / 2.0f;
      angle = 270.0f;
      text_x = (int)sprite_pos.x - bitmap_width / 2 - text_width - 1;
      text_y = (int)sprite_pos.y - text_glyph_height_ / 2;
    } else if (intersection.dx == -1) {
      sprite_pos.x = sprite_pos.x + (float)bitmap_height / 2.0f;
      angle = 90.0f;
      text_x = (int)sprite_pos.x + bitmap_width / 2 + 1;
      text_y = (int)sprite_pos.y - text_glyph_height_ / 2;
    } else if (intersection.dy == 1) {
      sprite_pos.y = sprite_pos.y - (float)bitmap_height / 2.0f;
      angle = 0;
      text_x = (int)sprite_pos.x - text_width / 2;
      text_y = (int)sprite_pos.y - bitmap_height / 2 - text_glyph_height_ - 1;
    } else {
      sprite_pos.y = sprite_pos.y + (float)bitmap_height / 2.0f;
      angle = 180.0f;
      text_x = (int)sprite_pos.x - text_width / 2;
      text_y = (int)sprite_pos.y + bitmap_height / 2 + 1;
    }

    playdate_->graphics->drawRotatedBitmap(bitmap, (int)sprite_pos.x,
                                           (int)sprite_pos.y, angle, 0.5f, 0.5f,
                                           1.0f, 1.0f);

    if (is_arrow_text_visble_) {
      playdate_->graphics->setFont(
          Fonts::instance().use(FontName::kFontBoldOutlined));

      playdate_->graphics->drawText(text.data(), text.size(), kASCIIEncoding,
                                    text_x, text_y);
    }
  }
}
