#include "asteroid.hpp"

void Asteroid::Update(float dt) { (void)dt; }

void Asteroid::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));
}

void Asteroid::drawDebug(const Point2d& position) {
  playdate_->graphics->drawEllipse((int)position.x, (int)position.y, size_,
                                   size_, 1, 0, 0, kColorBlack);
}
