#include "ui_station.hpp"

#include "fonts.hpp"
#include "pd_helpers.hpp"

void UiStation::Load() {
  const char* error = nullptr;

  job_card_ = playdate_->graphics->loadBitmap("data/job_card.png", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load job card, error: %s",
                                    error);
  }

  dot_1_ = playdate_->graphics->loadBitmap("data/dot_1.png", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load dot 1, error: %s", error);
  }

  dot_2_ = playdate_->graphics->loadBitmap("data/dot_2.png", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load dot 2, error: %s", error);
  }

  dot_3_ = playdate_->graphics->loadBitmap("data/dot_3.png", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load dot 3, error: %s", error);
  }

  a_button_pressed_ =
      playdate_->graphics->loadBitmap("data/a_pressed.png", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load A pressed, error: %s",
                                    error);
  }

  a_button_ = playdate_->graphics->loadBitmap("data/a_base.png", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load A base, error: %s", error);
  }
}

void UiStation::Update(float dt) {
  (void)dt;

  PDButtons buttons_current;
  PDButtons buttons_pushed;
  PDButtons buttons_released;
  playdate_->system->getButtonState(&buttons_current, &buttons_pushed,
                                    &buttons_released);
  if (buttons_released & kButtonUp) {
    if (cur_mission_ > 0) {
      --cur_mission_;
    }
  } else if (buttons_released & kButtonDown) {
    if (cur_mission_ + 1 < (int)missions_.size()) {
      ++cur_mission_;
    }
  }

  is_a_pressed_ = (buttons_current & kButtonA);

  if (buttons_released & kButtonA) {
    callback_->OnSelectMission(cur_mission_);
  }
}

void UiStation::Draw() {
  int screen_width = playdate_->display->getWidth();
  int screen_height = playdate_->display->getHeight();

  if (mode_ == Mode::MISSIONS) {
    playdate_->graphics->drawBitmap(job_card_, 0, 0, kBitmapUnflipped);

    playdate_->graphics->setFont(
        Fonts::instance().use(FontName::kFontBoldOutlined));

    playdate_->graphics->drawText(missions_[cur_mission_].name.data(),
                                  missions_[cur_mission_].name.size(),
                                  kASCIIEncoding, 38, 49);

    playdate_->graphics->drawText(missions_[cur_mission_].desc.data(),
                                  missions_[cur_mission_].desc.size(),
                                  kASCIIEncoding, 38, 77);

    playdate_->graphics->drawText(
        missions_[cur_mission_].destination_str.data(),
        missions_[cur_mission_].destination_str.size(), kASCIIEncoding, 38,
        150);

    playdate_->graphics->drawText(
        missions_[cur_mission_].cargo_durability_str.data(),
        missions_[cur_mission_].cargo_durability_str.size(), kASCIIEncoding, 38,
        177);

    playdate_->graphics->drawText(missions_[cur_mission_].difficulty_str.data(),
                                  missions_[cur_mission_].difficulty_str.size(),
                                  kASCIIEncoding, 38, 204);

    playdate_->graphics->drawText(missions_[cur_mission_].time_limit_str.data(),
                                  missions_[cur_mission_].time_limit_str.size(),
                                  kASCIIEncoding, 232, 177);

    playdate_->graphics->drawText(missions_[cur_mission_].price_str.data(),
                                  missions_[cur_mission_].price_str.size(),
                                  kASCIIEncoding, 232, 204);

    int bitmap_width = 0;
    int bitmap_height = 0;

    LCDBitmap* dots_bitmap = dot_1_;
    if (cur_mission_ == 0) {
      dots_bitmap = dot_1_;
    } else if (cur_mission_ == 1) {
      dots_bitmap = dot_2_;
    } else if (cur_mission_ == 2) {
      dots_bitmap = dot_3_;
    }

    GetBitmapSizes(playdate_, dots_bitmap, bitmap_width, bitmap_height);
    playdate_->graphics->drawBitmap(
        dots_bitmap, 379, (screen_height - 40 - bitmap_height) / 2 + 40,
        kBitmapUnflipped);

    LCDBitmap* a_button_bitmap = a_button_;
    if (is_a_pressed_) {
      a_button_bitmap = a_button_pressed_;
    }

    GetBitmapSizes(playdate_, a_button_bitmap, bitmap_width, bitmap_height);
    playdate_->graphics->drawBitmap(
        a_button_bitmap, screen_width - bitmap_width - 7,
        screen_height - bitmap_height - 7, kBitmapUnflipped);
  }
}
