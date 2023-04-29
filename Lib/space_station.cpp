#include "space_station.hpp"

#include <algorithm>

void SpaceStation::Update(float dt) {
  std::for_each(asteroids_.begin(), asteroids_.end(),
                [dt](auto& a) { a.Update(dt); });
}

void SpaceStation::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));

  std::for_each(asteroids_.begin(), asteroids_.end(),
                [&](auto& a) { a.Draw(camera); });
}

void SpaceStation::drawDebug(const Point2d& position) {
  playdate_->graphics->drawLine((int)position.x - 30, (int)position.y - 30,
                                (int)position.x + 30, (int)position.y - 30, 3,
                                kColorBlack);
  playdate_->graphics->drawLine((int)position.x + 30, (int)position.y - 30,
                                (int)position.x + 30, (int)position.y + 30, 3,
                                kColorBlack);
  playdate_->graphics->drawLine((int)position.x + 30, (int)position.y + 30,
                                (int)position.x - 30, (int)position.y + 30, 3,
                                kColorBlack);
  playdate_->graphics->drawLine((int)position.x - 30, (int)position.y + 30,
                                (int)position.x - 30, (int)position.y - 30, 3,
                                kColorBlack);
}

void SpaceStation::createAsteroids() {
  constexpr int num = 300;

  for (int i = 0; i < num; ++i) {
    // random size 10,20,30
    Asteroid a(playdate_, 10 * (1 + rand() % 3));
    // random possition
    auto distance = 300 + rand() % 1500;
    auto angle = DegToRad(rand() % 360);

    a.SetPosition(Point2d(distance * cos(angle), distance * sin(angle)));
    asteroids_.emplace_back(std::move(a));
  }
}