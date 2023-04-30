#include "asteroid.hpp"

void Asteroid::Update(float dt) { (void)dt; }

void Asteroid::Draw(const Camera& camera) {
  draw(camera.ConvertToCameraSpace(position_));
  if (kDrawDebugAsteroids) {
    drawDebug(camera.ConvertToCameraSpace(position_));
  }
}

void Asteroid::draw(const Point2d& position) {
  LCDBitmap* bitmap = type_->bitmaps[0];

  int bitmap_width = 0;
  int bitmap_height = 0;
  int bitmap_row_bytes = 0;
  uint8_t* bitmap_mask = 0;
  uint8_t* bitmap_data = 0;
  playdate_->graphics->getBitmapData(bitmap, &bitmap_width, &bitmap_height,
                                     &bitmap_row_bytes, &bitmap_mask,
                                     &bitmap_data);

  int x = (int)position.x - bitmap_width / 2;
  int y = (int)position.y - bitmap_height / 2;
  playdate_->graphics->drawBitmap(bitmap, x, y, kBitmapUnflipped);
}

void Asteroid::drawDebug(const Point2d& position) {
  float radius = GetRadius();
  playdate_->graphics->drawEllipse(
      (int)(position.x - radius), (int)(position.y - radius),
      (int)(radius * 2.0f), (int)(radius * 2.0f), 1, 0, 0, kColorWhite);
}
