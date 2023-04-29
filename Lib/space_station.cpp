#include "space_station.hpp"

void SpaceStation::Update(float dt) { (void)dt; }

void SpaceStation::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));
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
