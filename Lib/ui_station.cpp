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
}

void UiStation::Update(float dt) { (void)dt; }

void UiStation::Draw() {
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
  }
}
