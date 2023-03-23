#include "game.h"

#include "PdSymphony/point2d.hpp"
#include "PdSymphony/vector2d.hpp"

class Game {
 public:
  Game(PlaydateAPI* playdate) : playdate_(playdate) { void onStart(); }

  int Update() {
    float cur_time = playdate_->system->getElapsedTime();
    float dt = cur_time - prev_time_;
    prev_time_ = cur_time;
    onUpdateAndDraw(dt);

    // Redraw the screen.
    return 0;
  }

 private:
  void onStart() { prev_time_ = playdate_->system->getElapsedTime(); }

  void onUpdateAndDraw(float dt) {}

  PlaydateAPI* playdate_;
  float prev_time_;
};

void* SetupGame(PlaydateAPI* playdate) { return new Game(playdate); }

int Update(void* userdata) {
  Game* game = (Game*)userdata;
  return game->Update();
}
