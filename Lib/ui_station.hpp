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

  UiStation(PlaydateAPI* playdate) : playdate_(playdate) { (void)playdate_; }

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

  void ShowDelivery() { mode_ = Mode::DELIVERY; }

  void ShowStationInfo() { mode_ = Mode::STATION_INFO; }

  void ShowMissions() { mode_ = Mode::MISSIONS; }

 private:
  enum class Mode { IDLE, DELIVERY, STATION_INFO, MISSIONS };

  PlaydateAPI* playdate_{nullptr};
  Callback* callback_{nullptr};
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
