#include "game.h"

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "space_craft.hpp"

class Game {
 public:
  Game(PlaydateAPI *playdate)
      : playdate_(playdate), camera_(playdate), space_craft_(playdate) {
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

    camera_.SetLookAt(Point2d(0.0f, 0.0f));
  }

  void onUpdateAndDraw(float dt) {
    (void)dt;
    playdate_->graphics->clear(kColorWhite);

    space_craft_.UpdateAndDraw(dt, camera_);

    playdate_->system->drawFPS(5, 5);
  }

  PlaydateAPI *playdate_;
  float prev_time_;

  Camera camera_;
  SpaceCraft space_craft_;
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
