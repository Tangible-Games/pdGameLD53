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
  void onStart() {
    playdate_->system->logToConsole("#onStart");

    space_craft_.SetPosition(Point2d(spaceCraftPosX, spaceCraftPosY));
    space_station_.SetPosition(Point2d(0.0f, 0.0f));
    camera_.SetLookAt(space_craft_.GetPosition());
  }

  void onUpdateAndDraw(float dt) {
    (void)dt;
    playdate_->graphics->clear(kColorWhite);

    space_station_.Update(dt);

    stars_.Update(dt);

    space_craft_.Update(dt);
    camera_.SetLookAt(space_craft_.GetPosition());

    stars_.Draw(camera_);
    space_station_.Draw(camera_);
    space_craft_.Draw(camera_);

    drawLineToStation(camera_);

    playdate_->system->drawFPS(5, 5);
  }

  void drawLineToStation(const Camera &camera) {
    Point2d p1 = camera.ConvertToCameraSpace(space_craft_.GetPosition());
    Point2d p2 = camera.ConvertToCameraSpace(space_station_.GetPosition());

    playdate_->graphics->drawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, 1,
                                  kColorBlack);
  }

  PlaydateAPI *playdate_;
  float prev_time_;

  Camera camera_;
  SpaceCraft space_craft_;
  SpaceStation space_station_;
  Stars stars_;
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
