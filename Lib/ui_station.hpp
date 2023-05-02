#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "consts.hpp"
#include "pd_api.h"

using namespace PdSymphony::Math;

class UiStation {
 public:
  class Callback {
   public:
    virtual void OnSelectMission(int mission_index) = 0;
  };

  UiStation(PlaydateAPI* playdate)
      : playdate_(playdate),
        station_screen_intro_header_("My dear child!"),
        station_screen_intro_desc_(
            "I believe my lawyer gave you this letter.\nSave your tears, "
            "you'll soon be in a lot more trouble.\nI bequeath you my "
            "spaceship...\nWell, more like a space-beaten old truck.\nGo to "
            "the "
            "vastness of space, make a lot of money\nand pay back my gigantic "
            "debt.\nA couple of centuries should be enough.\n\n                "
            " "
            "                                                                  "
            "                      Your grandfather.") {
    (void)playdate_;
  }

  void RegisterCallback(Callback* callback) { callback_ = callback; }

  void Load();
  void Update(float dt);
  void Draw();

  void SetDelivery(const MissionDesc& delivery, float delivery_time,
                   float crate_health_percent, int money) {
    delivery_ = delivery;
    result_delivery_time_ = delivery_time;
    result_crate_health_percent_ = crate_health_percent;
    result_money_ = money;
  }

  void SetStation(const StationArea& station, int money) {
    station_ = station;
    money_ = money;
  }

  void SetMissions(const std::vector<MissionDesc>& missions) {
    missions_ = missions;
    cur_mission_ = 0;
  }

  void ShowIntro() { mode_ = Mode::INTRO; }

  void ShowDelivery() { mode_ = Mode::DELIVERY; }

  void ShowStationInfo() { mode_ = Mode::STATION_INFO; }

  void ShowMissions() { mode_ = Mode::MISSIONS; }

 private:
  enum class Mode { IDLE, INTRO, DELIVERY, STATION_INFO, MISSIONS };

  PlaydateAPI* playdate_{nullptr};
  Callback* callback_{nullptr};
  const std::string station_screen_intro_header_{};
  const std::string station_screen_intro_desc_{};
  LCDBitmap* station_screen_intro_{nullptr};
  LCDBitmap* mission_results_{nullptr};
  LCDBitmap* station_screen_{nullptr};
  LCDBitmap* job_card_{nullptr};
  LCDBitmap* dot_1_{nullptr};
  LCDBitmap* dot_2_{nullptr};
  LCDBitmap* dot_3_{nullptr};
  bool is_a_pressed_{false};
  LCDBitmap* a_button_pressed_{nullptr};
  LCDBitmap* a_button_{nullptr};
  Mode mode_{Mode::IDLE};
  MissionDesc delivery_;
  float result_delivery_time_{0.0f};
  float result_crate_health_percent_{0.0f};
  int result_money_{0};
  StationArea station_;
  int money_{0};
  int cur_mission_{0};
  std::vector<MissionDesc> missions_;
};
