#include "game.h"

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "space_craft.hpp"
#include "space_station.hpp"
#include "stars.hpp"

class Game {
 public:
  Game(PlaydateAPI *playdate)
      : playdate_(playdate),
        camera_(playdate),
        space_craft_(playdate),
        space_station_(playdate),
        stars_(playdate) {
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
    // TODO: use accelerometer???
    return playdate_->system->getCurrentTimeMilliseconds();
  }

  void onStart() {
    playdate_->system->logToConsole("#onStart");

    space_station_cur_ = 0;
    space_station_target_ = 0;
    size_t idx = 0;
    std::for_each(stations_.begin(), stations_.end(), [&](auto &s) {
      s.pos = kStationPos[idx++];
      s.seed = getSeed();
    });

    space_station_.SetPosition(Point2d(0.0f, 0.0f));
    space_craft_.SetPosition(Point2d(kSpaceCraftPosX, kSpaceCraftPosY));

    onUpdateArea(0);
  }

  void onUpdateArea(uint32_t idx) {
    playdate_->system->logToConsole("#onUpdateArea %d", idx);
    auto &seed = stations_[idx].seed;
    space_station_.Generate(seed);
    stars_.Generate(seed);
    space_craft_.ResetSpaceStation(&space_station_);

    if (space_station_cur_ != space_station_target_) {
      Vector2d s = stations_[space_station_cur_].pos -
                   stations_[space_station_target_].pos;
      s = s.GetNormalized() *
          (kAsteroidAreaDistance + kAsteroidToBaseAreaDistance);

      playdate_->system->logToConsole("#onUpdateArea new pos %d, %d", (int)s.x,
                                      (int)s.y);

      space_craft_.SetPosition(Point2d(s.x, s.y));
    }
    space_craft_.SetVelocity(Vector2d(0, 0));

    camera_.SetLookAt(space_craft_.GetPosition());

    space_station_cur_ = idx;
  }

  void onUpdateAndDraw(float dt) {
    (void)dt;
    playdate_->graphics->clear(kColorBlack);

    space_station_.Update(dt);

    stars_.Update(dt);

    space_craft_.Update(dt);
    setupCamera();

    updateState();

    stars_.Draw(camera_);
    space_station_.Draw(camera_);
    space_craft_.Draw(camera_);

    drawLineToStation(camera_);

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
        if (craft_to_station < kSpaceStationSize) {
          target_state_ = TargetState::READY_TO_GET;
        }
        break;
      case TargetState::READY_TO_GET:
        if (craft_to_station > kSpaceStationSize) {
          target_state_ = TargetState::NONE;
        } else if (buttons_current & kButtonA) {
          setDebugTarget();
          target_state_ = TargetState::SET;
        }
        break;
      case TargetState::SET:
        if (craft_to_station >
            kAsteroidToBaseAreaDistance + kAsteroidAreaDistance) {
          target_state_ = TargetState::READY_TO_JUMP;
        }
        break;
      case TargetState::READY_TO_JUMP:
        if (craft_to_station <
            kAsteroidToBaseAreaDistance + kAsteroidAreaDistance) {
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
      case TargetState::READY_TO_GET:
        out = "Press A to get task";
        break;
      case TargetState::SET: {
        Point2d p1 =
            camera_.ConvertToCameraSpace(stations_[space_station_cur_].pos,
                                         stations_[space_station_cur_].pos);
        Point2d p2 =
            camera_.ConvertToCameraSpace(stations_[space_station_target_].pos,
                                         stations_[space_station_cur_].pos);
        Segment2d s{p1, p2};
        Point2d intersect;
        Vector2d direction{0, 0};
        const Point2d p00{0, 0};
        const Point2d p01{playdate_->display->getWidth() * 1.0f, 0};
        const Point2d p11{playdate_->display->getWidth() * 1.0f,
                          playdate_->display->getHeight() * 1.0f};
        const Point2d p10{0, playdate_->display->getHeight() * 1.0f};
        if (s.Intersect(Segment2d(p00, p01), 0.001f, intersect)) {
          direction = {0, 1};
        } else if (s.Intersect(Segment2d(p10, p11), 0.001f, intersect)) {
          direction = {0, -1};
        } else if (s.Intersect(Segment2d(p00, p10), 0.001f, intersect)) {
          direction = {1, 0};
        } else if (s.Intersect(Segment2d(p01, p11), 0.001f, intersect)) {
          direction = {-1, 0};
        } else {
          break;
        }
        Point2d front = intersect + direction * 10.0f;
        Vector2d right_direction = direction.GetRotated(DegToRad(-90.0f));
        Point2d right = intersect + right_direction * 10.0f - direction * 20.0f;
        Point2d left = intersect - right_direction * 10.0f - direction * 20.0f;
        playdate_->graphics->drawLine((int)front.x, (int)front.y, (int)right.x,
                                      (int)right.y, 3, kColorWhite);
        playdate_->graphics->drawLine((int)right.x, (int)right.y, (int)left.x,
                                      (int)left.y, 3, kColorWhite);
        playdate_->graphics->drawLine((int)left.x, (int)left.y, (int)front.x,
                                      (int)front.y, 3, kColorWhite);

      } break;
      case TargetState::READY_TO_JUMP:
        out = "Press A to jump";
        break;
      default:
        break;
    }
    if (out) {
      playdate_->graphics->drawText(out, strlen(out), kASCIIEncoding,
                                    playdate_->display->getWidth() / 2 - 100,
                                    1);
    }
  }

  void setupCamera() {
    Vector2d to_station_norm =
        (space_station_.GetPosition() - space_craft_.GetPosition())
            .GetNormalized();
    camera_.SetLookAt(space_craft_.GetPosition() +
                      to_station_norm * kSpaceCraftCameraOffset);
  }

  void drawLineToStation(const Camera &camera) {
    Point2d p1 = camera.ConvertToCameraSpace(space_craft_.GetPosition());
    Point2d p2 = camera.ConvertToCameraSpace(space_station_.GetPosition());

    playdate_->graphics->drawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, 1,
                                  kColorWhite);
  }

  PlaydateAPI *playdate_;
  float prev_time_;

  Camera camera_;
  SpaceCraft space_craft_;
  SpaceStation space_station_;
  Stars stars_;

  std::array<StationArea, kStationsNum> stations_;
  // current state
  size_t space_station_cur_{0};
  size_t space_station_target_{0};
  enum TargetState {
    NONE,
    READY_TO_GET,
    SET,
    READY_TO_JUMP,
    JUMP,
  } target_state_{TargetState::NONE};
};

void *SetupGame(PlaydateAPI *playdate) {
  static Game game(playdate);
  playdate->system->logToConsole("#SetupGame");
  return &game;
}

int Update(void *userdata) {
  Game *game = (Game *)userdata;
  return game->Update();
}
