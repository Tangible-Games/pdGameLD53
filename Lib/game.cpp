#include "game.h"

#include "PdSymphony/all_symphony.hpp"

class Game {
 public:
  Game(PlaydateAPI *playdate) : playdate_(playdate) { onStart(); }

  int Update() {
    float cur_time = playdate_->system->getElapsedTime();
    float dt = cur_time - prev_time_;
    prev_time_ = cur_time;
    onUpdateAndDraw(dt);

    // Redraw the screen.
    return 1;
  }

 private:
  void onStart() { playdate_->system->logToConsole("#onStart"); }

  void onUpdateAndDraw(float dt) {
    (void)dt;
    playdate_->graphics->clear(kColorWhite);

    playdate_->system->drawFPS(5, 5);
  }

  PlaydateAPI *playdate_;
  float prev_time_;
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
