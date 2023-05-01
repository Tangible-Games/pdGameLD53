#include "stars.hpp"

#include <algorithm>

void Stars::Update(float dt) { (void)dt; }

void Stars::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));
}

void Stars::drawDebug(const Point2d& position) {
  std::for_each(stars_.begin(), stars_.end(), [&](auto& s) {
    float x = s.p.x + position.x / velocity_ratio_;
    float y = s.p.y + position.y / velocity_ratio_;

    x = x - floor(x / (float)width_) * (float)width_;
    y = y - floor(y / (float)height_) * (float)height_;

    playdate_->graphics->fillRect(x, y, s.size, s.size, kColorWhite);
  });
}
