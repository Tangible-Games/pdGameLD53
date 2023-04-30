#include "asteroid.hpp"

void Asteroid::Update(float dt) { (void)dt; }

void Asteroid::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));
}

void Asteroid::drawDebug(const Point2d& position) {
  playdate_->graphics->drawEllipse(
      (int)(position.x - radius_), (int)(position.y - radius_),
      (int)(radius_ * 2.0f), (int)(radius_ * 2.0f), 1, 0, 0, kColorWhite);
}
