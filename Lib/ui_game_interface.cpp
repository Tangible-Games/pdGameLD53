#include "ui_game_interface.hpp"

#include "consts.hpp"
#include "pd_helpers.hpp"

void UiGameInterface::Load() {
  const char* error = nullptr;

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

  clock_ = playdate_->graphics->loadBitmapTable("data/clock.gif", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load clock, error: %s", error);
  }
}

void UiGameInterface::Update(float dt) { running_time_ += dt; }

void UiGameInterface::Draw() {
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

  GetBitmapSizes(playdate_, crate_, bitmap_width, bitmap_height);
  playdate_->graphics->drawBitmap(crate_, screen_width - bitmap_width - 15,
                                  screen_height - bitmap_height - 15,
                                  kBitmapUnflipped);

  LCDBitmap* bitmap = nullptr;

  bitmap = SelectFrameLooped(playdate_, clock_, kUiClockAnimationLength,
                             kUiClockAnimationNumFrames, running_time_);
  GetBitmapSizes(playdate_, bitmap, bitmap_width, bitmap_height);
  playdate_->graphics->drawBitmap(
      bitmap, 15, screen_height - bitmap_height - 15, kBitmapUnflipped);
}
