#include "stars.hpp"

#include <algorithm>

void Stars::Update(float dt) { (void)dt; }

void Stars::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));
}

void Stars::drawDebug(const Point2d& position) {
  std::for_each(stars_.begin(), stars_.end(), [&](auto& s) {
    playdate_->graphics->drawRect(
        (int)(s.x + position.x / kStarsVelocitySlowDown) % width_,
        (int)(s.y + +position.y / kStarsVelocitySlowDown) % height_, 1, 1,
        kColorBlack);
  });
}
