#include "game.h"

#include <iostream>

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_helpers.hpp"
#include "space_craft.hpp"
#include "space_station.hpp"
#include "stars.hpp"
#include "ui_game_interface.hpp"

class Game {
 public:
  Game(PlaydateAPI *playdate)
      : playdate_(playdate),
        camera_(playdate),
        space_craft_(playdate),
        space_station_(playdate),
        stars_(playdate),
        game_interface_(playdate) {
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
  uint32_t getSeed() {
    uint32_t currentTime = playdate_->system->getCurrentTimeMilliseconds();
    // enable accelerometer
    playdate_->system->setPeripheralsEnabled(kAccelerometer);
    // Get accelerometer data
    float accelX, accelY, accelZ;
    playdate_->system->getAccelerometer(&accelX, &accelY, &accelZ);
    // disable accelerometer
    playdate_->system->setPeripheralsEnabled(kNone);
    float batPercent = playdate_->system->getBatteryPercentage();
    uint32_t seed = currentTime;
    seed ^= ((uint32_t)(accelX * 17));
    seed ^= ((uint32_t)(accelY * 13));
    seed ^= ((uint32_t)(accelZ * 23));
    seed ^= ((uint32_t)(batPercent * 19));
    return seed;
  }

  void onStart() {
    playdate_->system->logToConsole("#onStart");

    space_station_cur_ = 0;
    space_station_target_ = 0;
    space_station_.SetPosition(Point2d(0.0f, 0.0f));
    space_craft_.SetPosition(Point2d(kSpaceCraftPosX, kSpaceCraftPosY));

    const char *error = nullptr;
    arrow_bitmap_table_ =
        playdate_->graphics->loadBitmapTable("data/triangle_3.gif", &error);
    if (error) {
      playdate_->system->logToConsole("Failed to load arrow, error: %s", error);
    }

    // Load all fonts from consts.hpp kFontDataPath
    for (int i = 0; i < kFontLast; i++) {
      error = nullptr;
      fonts_[i] = playdate_->graphics->loadFont(kFontDataPath[i], &error);
      if (error) {
        playdate_->system->logToConsole("Failed to load font, error: %s",
                                        error);
      }
    }

    game_interface_.Load();

    onUpdateArea(0);
  }

  void onUpdateArea(uint32_t idx) {
    playdate_->system->logToConsole("#onUpdateArea %d", idx);

    space_station_.Generate(stations_[idx]);
    stars_.Generate(stations_[idx].seed);
    space_craft_.ResetSpaceStation(&space_station_);

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

    updateState();

    stars_.Draw(camera_);
    space_station_.Draw(camera_);
    space_craft_.Draw(camera_);

    drawArrowToStation(camera_);

    game_interface_.Update(dt);
    game_interface_.Draw();

    playdate_->system->drawFPS(5, 5);

    showState();
  }

  void onJump() { onUpdateArea(space_station_target_); }

  void setDebugTarget() {
    // random station from list
    space_station_target_ =
        (space_station_cur_ + 1 + (rand() % (stations_.size() - 1))) %
        stations_.size();
    playdate_->system->logToConsole("setDebugTarget %d", space_station_target_);
  }

  void updateState() {
    auto craft_to_station =
        (space_craft_.GetPosition() - space_station_.GetPosition()).GetLength();
    PDButtons buttons_current;
    PDButtons buttons_pushed;
    PDButtons buttons_released;
    playdate_->system->getButtonState(&buttons_current, &buttons_pushed,
                                      &buttons_released);

    switch (target_state_) {
      case TargetState::NONE:
        if (craft_to_station < kSpaceStationRadius) {
          target_state_ = TargetState::READY_TO_DOCK;
        }
        break;
      case TargetState::READY_TO_DOCK:
        if (craft_to_station > kSpaceStationRadius) {
          target_state_ = TargetState::NONE;
        } else if (buttons_current & kButtonA) {
          setDebugTarget();
          target_state_ = TargetState::SET;
        }
        break;
      case TargetState::SET:
        if (craft_to_station >
            stations_[space_station_cur_].asteroids_to_base_distance +
                stations_[space_station_cur_].asteroids_area_distance) {
          target_state_ = TargetState::READY_TO_JUMP;
        }
        break;
      case TargetState::READY_TO_JUMP:
        if (craft_to_station <
            stations_[space_station_cur_].asteroids_to_base_distance +
                stations_[space_station_cur_].asteroids_area_distance) {
          target_state_ = TargetState::SET;
        } else if (buttons_current & kButtonA) {
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

  void showState() {
    const char *out{nullptr};
    switch (target_state_) {
      case TargetState::READY_TO_DOCK:
        out = "Press A to get task";
        break;
      case TargetState::SET:
        break;
      case TargetState::READY_TO_JUMP:
        out = "Press A to jump";
        break;
      default:
        break;
    }
    if (out) {
      playdate_->graphics->setFont(fonts_[kFontBoldOutlined]);
      playdate_->graphics->drawText(out, strlen(out), kASCIIEncoding,
                                    playdate_->display->getWidth() / 2 - 100,
                                    1);
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

  void drawArrowToStation(const Camera &camera) {
    int screen_width = playdate_->display->getWidth();
    int screen_height = playdate_->display->getHeight();
    AARect2d screen_rect(
        Point2d((float)screen_width / 2.0f, (float)screen_height / 2.0f),
        Vector2d((float)screen_width / 2.0f, (float)screen_height / 2.0f));

    Point2d ship_in_camera =
        camera.ConvertToCameraSpace(space_craft_.GetPosition());

    bool is_visible = true;

    Vector2d ray_dir(0.0f, -1.0f);
    if (target_state_ == TargetState::SET ||
        target_state_ == TargetState::READY_TO_JUMP) {
      ray_dir = (stations_[space_station_target_].pos -
                 stations_[space_station_cur_].pos)
                    .GetNormalized();
    } else {
      Point2d station_in_camera =
          camera.ConvertToCameraSpace(space_station_.GetPosition());
      ray_dir = (station_in_camera - ship_in_camera).GetNormalized();

      if (screen_rect.IsPointInside(station_in_camera)) {
        is_visible = false;
      }
    }

    if (is_visible) {
      AARect2d::FromInsideIntersection intersection;
      screen_rect.IntersectRayFromInside(ship_in_camera, ray_dir, intersection);

      LCDBitmap *bitmap = SelectFrameLooped(
          playdate_, arrow_bitmap_table_, kUiArrowAnimationLength,
          kUiArrowAnimationNumFrames, running_time_);

      int bitmap_width = 0;
      int bitmap_height = 0;
      GetBitmapSizes(playdate_, bitmap, bitmap_width, bitmap_height);

      Point2d sprite_pos = intersection.p;
      float angle = 0.0f;
      if (intersection.dx == 1) {
        sprite_pos.x = sprite_pos.x - (float)bitmap_width / 2.0f;
        angle = 270.0f;
      } else if (intersection.dx == -1) {
        sprite_pos.x = sprite_pos.x + (float)bitmap_height / 2.0f;
        angle = 90.0f;
      } else if (intersection.dy == 1) {
        sprite_pos.y = sprite_pos.y - (float)bitmap_height / 2.0f;
        angle = 0;
      } else {
        sprite_pos.y = sprite_pos.y + (float)bitmap_height / 2.0f;
        angle = 180.0f;
      }

      playdate_->graphics->drawRotatedBitmap(bitmap, (int)sprite_pos.x,
                                             (int)sprite_pos.y, angle, 0.5f,
                                             0.5f, 1.0f, 1.0f);
    }
  }

  PlaydateAPI *playdate_;
  float prev_time_;

  Camera camera_;
  SpaceCraft space_craft_;
  SpaceStation space_station_;
  Stars stars_;

  std::vector<StationArea> stations_{GetStations()};

  // current state
  size_t space_station_cur_{0};
  size_t space_station_target_{0};
  enum TargetState {
    NONE,
    READY_TO_DOCK,
    SET,
    READY_TO_JUMP,
    JUMP,
  } target_state_{TargetState::NONE};

  LCDBitmapTable *arrow_bitmap_table_{nullptr};

  UiGameInterface game_interface_;

  std::array<LCDFont *, kFontLast> fonts_;

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
