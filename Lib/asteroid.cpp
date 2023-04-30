#include "asteroid.hpp"

#include "pd_helpers.hpp"

void Asteroid::Update(float dt) { (void)dt; }

void Asteroid::Draw(const Camera& camera) {
  draw(camera.ConvertToCameraSpace(position_));
  if (kDrawDebugAsteroids) {
    drawDebug(camera.ConvertToCameraSpace(position_));
  }
}

void Asteroid::draw(const Point2d& position) {
  DrawBitmapCentered(playdate_, type_->bitmaps[bitmap_index_], position);
}

void Asteroid::drawDebug(const Point2d& position) {
  float radius = GetRadius();
  playdate_->graphics->drawEllipse(
      (int)(position.x - radius), (int)(position.y - radius),
      (int)(radius * 2.0f), (int)(radius * 2.0f), 1, 0, 0, kColorWhite);
}
