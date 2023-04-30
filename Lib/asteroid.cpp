#include "asteroid.hpp"

void Asteroid::Update(float dt) { (void)dt; }

void Asteroid::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));
}

void Asteroid::drawDebug(const Point2d& position) {
  float radius = GetRadius();
  playdate_->graphics->drawEllipse(
      (int)(position.x - radius), (int)(position.y - radius),
      (int)(radius * 2.0f), (int)(radius * 2.0f), 1, 0, 0, kColorWhite);
}
