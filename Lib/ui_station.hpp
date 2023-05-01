#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "consts.hpp"
#include "pd_api.h"

using namespace PdSymphony::Math;

class UiStation {
 public:
  UiStation(PlaydateAPI* playdate) : playdate_(playdate) { (void)playdate_; }

  void Load();
  void Update(float dt);
  void Draw();

  void SetMissions(const std::vector<MissionDesc>& missions) {
    missions_ = missions;
    cur_mission_ = 0;
  }

  void ShowMissions() { mode_ = Mode::MISSIONS; }

 private:
  enum class Mode { MISSIONS };

  PlaydateAPI* playdate_{nullptr};
  LCDBitmap* job_card_{nullptr};
  Mode mode_{Mode::MISSIONS};
  int cur_mission_{0};
  std::vector<MissionDesc> missions_;
};
