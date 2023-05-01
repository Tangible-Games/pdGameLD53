#include "game.h"

#include <iostream>

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "fonts.hpp"
#include "pd_helpers.hpp"
#include "sounds.hpp"
#include "space_craft.hpp"
#include "space_station.hpp"
#include "stars.hpp"
#include "ui_game_interface.hpp"
#include "ui_station.hpp"

class Game : public SpaceCraft::Callback, public UiStation::Callback {
 public:
  Game(PlaydateAPI *playdate)
      : playdate_(playdate),
        camera_(playdate),
        space_craft_(playdate),
        space_station_(playdate),
        stars_(playdate),
        game_interface_(playdate),
        ui_station_(playdate) {
    space_craft_.RegisterCallback(this);
    ui_station_.RegisterCallback(this);
    onStart();
  }

  int Update() {
    float cur_time = playdate_->system->getElapsedTime();
    float dt = cur_time - prev_time_;
    prev_time_ = cur_time;
    onUpdateAndDraw(dt);

    // Redraw the screen.
    return 1;
  }

 private:
  void onStart() {
    playdate_->system->logToConsole("#onStart");

    space_station_cur_ = 0;
    space_station_target_ = 0;
    space_station_.SetPosition(Point2d(0.0f, 0.0f));
    space_craft_.SetPosition(Point2d(kSpaceCraftPosX, kSpaceCraftPosY));

    Fonts::instance().loadFonts(playdate_);
    Sounds::instance().setup(playdate_);

    Sounds::instance().playMusic(kMusicMain);

    game_interface_.Load();
    ui_station_.Load();

    const char *error = nullptr;

    docking_bitmap_table_ =
        playdate_->graphics->loadBitmapTable("data/cut-prkng-copy.gif", &error);
    if (error) {
      playdate_->system->logToConsole(
          "Failed to load docking animation, error: %s", error);
    }

    game_interface_.SetTimeVisibility(false);
    game_interface_.SetCrateHealthVisibility(false);

    current_mission_ = -1;

    onUpdateArea(0);

    // hack to start from jump position
#if 0
    target_state_ = TargetState::STATION;
    GenMissions(space_station_cur_, missions_to_select_,
                    missions_to_select_indices_);
    OnSelectMission(0);
    space_craft_.SetVelocity(Vector2d(0, -100));
    space_craft_.SetPosition(Point2d(0, stations_[space_station_cur_].jump_distance + 1000));
#endif
  }

  void onUpdateArea(uint32_t idx) {
    playdate_->system->logToConsole("#onUpdateArea %d", idx);

    space_station_.Generate(stations_[idx]);
    stars_.Generate(stations_[idx].seed);
    space_craft_.ResetSpaceStation(&space_station_);

    space_craft_.Start();

    if (space_station_cur_ != space_station_target_) {
      Vector2d s = stations_[space_station_cur_].pos -
                   stations_[space_station_target_].pos;
      s = s.GetNormalized() *
          (stations_[space_station_cur_].asteroids_to_base_distance +
           stations_[space_station_cur_].asteroids_area_distance);

      playdate_->system->logToConsole("#onUpdateArea new pos %d, %d", (int)s.x,
                                      (int)s.y);

      space_craft_.SetPosition(Point2d(s.x, s.y));
    }
    space_craft_.SetVelocity(Vector2d(0, 0));

    camera_.SetLookAt(space_craft_.GetPosition());

    space_station_cur_ = idx;
  }

  void onUpdateAndDraw(float dt) {
    running_time_ += dt;

    playdate_->graphics->clear(kColorBlack);

    space_station_.Update(dt);

    stars_.Update(dt);

    space_craft_.Update(dt);

    setupCamera();
    updateState(dt);
    updateArrowToStation(camera_);

    game_interface_.SetSpeed(space_craft_.GetSpeed());
    game_interface_.Update(dt);

    ui_station_.Update(dt);

    // Drawing

    if (target_state_ == TargetState::DOCKING) {
      stars_.Draw(camera_);
      LCDBitmap *bitmap = SelectFrameLooped(
          playdate_, docking_bitmap_table_, kSpaceStationDockingAnimationLength,
          kSpaceStationDockingAnimationNumFrames, target_state_time_);

      playdate_->graphics->drawBitmap(bitmap, 0, 0, kBitmapUnflipped);
    } else if (target_state_ == TargetState::STATION) {
      ui_station_.Draw();
    } else {
      stars_.Draw(camera_);
      space_station_.Draw(camera_);
      space_craft_.Draw(camera_);
      game_interface_.Draw();
    }

    // playdate_->system->drawFPS(5, 5);

    onUpdateSounds();
  }

  void onUpdateSounds() { space_craft_.UpdateSounds(); }

  void onJump() { onUpdateArea(space_station_target_); }

  void updateState(float dt) {
    auto craft_to_station =
        (space_craft_.GetPosition() - space_station_.GetPosition()).GetLength();
    PDButtons buttons_current;
    PDButtons buttons_pushed;
    PDButtons buttons_released;
    playdate_->system->getButtonState(&buttons_current, &buttons_pushed,
                                      &buttons_released);

    if (current_mission_ != -1) {
      total_delivery_time_ += dt;
      if (delivery_time_ > 0.0f) {
        delivery_time_ -= (dt * kSpaceCraftDeliveryTimeFactor);
        if (delivery_time_ < 0.0f) {
          delivery_time_ = 0.0f;
        }
      }

      game_interface_.SetTimeSeconds(delivery_time_);
    }

    switch (target_state_) {
      case TargetState::NONE:
        if (craft_to_station < kSpaceStationRadius) {
          target_state_ = TargetState::READY_TO_DOCK;
        }
        break;
      case TargetState::READY_TO_DOCK: {
        if (craft_to_station > kSpaceStationRadius) {
          target_state_ = TargetState::NONE;
        } else {
          float speed = space_craft_.GetSpeed();
          if (speed > kSpaceStationDockSpeed) {
            game_interface_.SetMovingTooFastText(true);
          } else {
            game_interface_.SetMovingTooFastText(false);

            space_craft_.StartAligning(space_station_.GetPosition());
            target_state_ = TargetState::ALIGN_IN_DOCK;
            target_state_time_ = 0.0f;
          }
        }
      } break;
      case TargetState::ALIGN_IN_DOCK: {
        target_state_time_ += dt;
        if (target_state_time_ > kSpaceStationAlignTimeout) {
          target_state_ = TargetState::DOCKING;
          target_state_time_ = 0.0f;
        }
      } break;
      case TargetState::DOCKING:
        target_state_time_ += dt;
        if (target_state_time_ > kSpaceStationDockingAnimationLength) {
          GenMissions(space_station_cur_, missions_to_select_,
                      missions_to_select_indices_);
          if (current_mission_ != -1) {
            float money_factor = 1.0f;
            if (missions_[current_mission_].time_limit_sec > 0.0f) {
              if (total_delivery_time_ >
                  missions_[current_mission_].time_limit_sec) {
                money_factor *= kSpaceCraftDeliveryOutOfTimeFactor;
              }
            }

            float cargo_health_percent = 100.0f;
            if (missions_[current_mission_].cargo_durability > 0) {
              cargo_health_percent =
                  cargo_health_ / missions_[current_mission_].cargo_durability *
                  100.0f;
              money_factor *= (cargo_health_percent / 100.0f);
            }

            int money = (int)(missions_[current_mission_].price * money_factor);
            ui_station_.SetDelivery(missions_[current_mission_],
                                    total_delivery_time_, cargo_health_percent,
                                    money);
            money_ += money;
          }
          ui_station_.SetStation(stations_[space_station_cur_], money_);
          ui_station_.SetMissions(missions_to_select_);
          if (current_mission_ != -1) {
            ui_station_.ShowDelivery();
          } else {
            ui_station_.ShowStationInfo();
          }

          target_state_ = TargetState::STATION;
          target_state_time_ = kSpaceStationDockingAnimationLength;
        }
        break;
      case TargetState::STATION:
        break;
      case TargetState::SET:
        if (craft_to_station >
            stations_[space_station_cur_].asteroids_to_base_distance +
                stations_[space_station_cur_].asteroids_area_distance) {
          target_state_ = TargetState::READY_TO_JUMP;
        }
        break;
      case TargetState::READY_TO_JUMP:
        // no way back from here
        game_interface_.SetReadyToJump(true);
        // old way to jump
        if (buttons_current & kButtonA) {
            target_state_ = TargetState::JUMP;
        }
        break;
      case TargetState::JUMP:
        onJump();
        target_state_ = TargetState::NONE;
        break;
      default:
        break;
    }
  }

  void setupCamera() {
    Vector2d to_station_norm;
    float offset_factor = 1.0f;
    if (target_state_ == TargetState::SET ||
        target_state_ == TargetState::READY_TO_JUMP) {
      to_station_norm = (stations_[space_station_target_].pos -
                         stations_[space_station_cur_].pos)
                            .GetNormalized();
      offset_factor = kSpaceCraftToStationCameraOffset;
    } else if (target_state_ == TargetState::ALIGN_IN_DOCK ||
               target_state_ == TargetState::DOCKING) {
      camera_.SetLookAt(space_craft_.GetPosition());
    } else {
      Vector2d to_station =
          space_station_.GetPosition() - space_craft_.GetPosition();
      to_station_norm = to_station.GetNormalized();

      float d = to_station.GetLength();
      if (d > kSpaceCraftToStationCameraOffsetRadius) {
        d = kSpaceCraftToStationCameraOffsetRadius;
      }
      offset_factor = (d / kSpaceCraftToStationCameraOffsetRadius) *
                      kSpaceCraftToStationCameraOffset;
    }
    camera_.SetLookAt(space_craft_.GetPosition() +
                      to_station_norm * offset_factor);
  }

  void updateArrowToStation(const Camera &camera) {
    Point2d ship_in_camera =
        camera.ConvertToCameraSpace(space_craft_.GetPosition());

    bool is_visible = true;
    bool is_text_visible = true;

    Vector2d ray_dir(0.0f, -1.0f);
    float distance = 0.0f;
    if (target_state_ == TargetState::SET ||
        target_state_ == TargetState::READY_TO_JUMP) {
      ray_dir = (stations_[space_station_target_].pos -
                 stations_[space_station_cur_].pos)
                    .GetNormalized();
      is_text_visible = false;
    } else {
      distance = (space_station_.GetPosition() - space_craft_.GetPosition())
                     .GetLength();

      Point2d station_in_camera =
          camera.ConvertToCameraSpace(space_station_.GetPosition());
      ray_dir = (station_in_camera - ship_in_camera).GetNormalized();

      int screen_width = playdate_->display->getWidth();
      int screen_height = playdate_->display->getHeight();
      AARect2d screen_rect(
          Point2d((float)screen_width / 2.0f, (float)screen_height / 2.0f),
          Vector2d((float)screen_width / 2.0f, (float)screen_height / 2.0f));

      if (screen_rect.IsPointInside(station_in_camera)) {
        is_visible = false;
      }
    }

    game_interface_.SetArrow(is_visible, is_text_visible, ship_in_camera,
                             ray_dir, distance);
  }

  void GenMissions(int current_station_index,
                   std::vector<MissionDesc> &missions_out,
                   std::vector<int> &missions_indices_out) const {
    missions_out.clear();
    missions_indices_out.clear();

    std::vector<bool> taken;
    taken.resize(missions_.size());

    if (current_mission_ != -1) {
      taken[current_mission_] = true;
    }

    int num_tries = 3;

    for (int i = 0; i < 3; ++i) {
      int new_mission = -1;
      for (int k = 0; k < num_tries; ++k) {
        int mission_index = rand() % missions_.size();
        if (!taken[mission_index]) {
          new_mission = mission_index;
          break;
        }
      }
      if (new_mission != -1) {
        taken[new_mission] = true;
        missions_out.push_back(missions_[new_mission]);
        missions_indices_out.push_back(new_mission);
      }
    }

    for (int i = 0; i < (int)missions_out.size(); ++i) {
      int station_index = rand() % stations_.size();
      if (station_index == current_station_index) {
        station_index = (station_index + 1) % stations_.size();
      }
      missions_out[i].destination_index = station_index;
      missions_out[i].destination_str = stations_[station_index].name;
      missions_out[i].difficulty_str = stations_[station_index].difficulty_str;
      missions_out[i].difficulty = stations_[station_index].difficulty;
    }

    playdate_->system->logToConsole("Number of missions generated: %i",
                                    missions_out.size());
  }

  // SpaceCraft
  void OnHit(float impact) override {
    playdate_->system->logToConsole("Hit with impact: %f", (double)impact);

    if (current_mission_ != -1) {
      float damage = kSpaceCraftCollisionImpactToDamageBase +
                     impact * kSpaceCraftCollisionImpactToDamageRatio;
      cargo_health_ -= damage;
      if (cargo_health_ < 0.0f) {
        cargo_health_ = 0.0f;
      }

      game_interface_.SetCrateHealthPercent(
          cargo_health_ / missions_[current_mission_].cargo_durability *
          100.0f);
    }
  }

  // UiStation
  void OnSelectMission(int mission_index) override {
    playdate_->system->logToConsole("#OnSelectMission, mission_index: %i",
                                    mission_index);

    if (target_state_ == TargetState::STATION) {
      current_mission_ = missions_to_select_indices_[mission_index];
      const MissionDesc &mission = missions_to_select_[mission_index];

      playdate_->system->logToConsole("Mission: %i, %s", current_mission_,
                                      mission.name.c_str());

      space_station_target_ = mission.destination_index;
      playdate_->system->logToConsole(
          "Next station: %i, %s", space_station_target_,
          stations_[space_station_target_].name.c_str());

      delivery_time_ = mission.time_limit_sec;
      total_delivery_time_ = 0.0f;
      cargo_health_ = mission.cargo_durability;

      if (mission.cargo_durability > 0) {
        game_interface_.SetCrateHealthPercent(100.0f);
        game_interface_.SetCrateHealthVisibility(true);
      } else {
        game_interface_.SetCrateHealthVisibility(false);
      }

      if (mission.time_limit_sec > 0.0f) {
        game_interface_.SetTimeVisibility(true);
      } else {
        game_interface_.SetTimeVisibility(false);
      }

      target_state_ = TargetState::SET;

      space_craft_.Start();
    }
  }

  PlaydateAPI *playdate_;
  float prev_time_;

  Camera camera_;
  SpaceCraft space_craft_;
  SpaceStation space_station_;
  Stars stars_;

  std::vector<StationArea> stations_{GetStations()};
  std::vector<MissionDesc> missions_{GetMissions()};

  // current state
  int space_station_cur_{0};
  int space_station_target_{0};
  enum TargetState {
    NONE,
    READY_TO_DOCK,
    ALIGN_IN_DOCK,
    DOCKING,
    STATION,
    SET,
    READY_TO_JUMP,
    JUMP,
  } target_state_{TargetState::NONE};
  float target_state_time_{0.0f};

  int money_{0};
  int current_mission_{-1};
  float cargo_health_{0.0f};
  float delivery_time_{0.0f};
  float total_delivery_time_{0.0f};
  std::vector<MissionDesc> missions_to_select_;
  std::vector<int> missions_to_select_indices_;

  UiGameInterface game_interface_;
  UiStation ui_station_;

  LCDBitmapTable *docking_bitmap_table_{nullptr};

  float running_time_{0.0f};
};

static int test = 0;
static void __attribute__((constructor)) test_constructor(void) { test = 1234; }

void *SetupGame(PlaydateAPI *playdate) {
  static Game game(playdate);
  playdate->system->logToConsole("#SetupGame");
  playdate->system->logToConsole("test: %d", test);
  return &game;
}

int Update(void *userdata) {
  Game *game = (Game *)userdata;
  return game->Update();
}
