#include "stars.hpp"

#include <algorithm>

void Stars::Update(float dt) { (void)dt; }

void Stars::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));
}

void Stars::drawDebug(const Point2d& position) {
  std::for_each(stars_.begin(), stars_.end(), [&](auto& s) {
    playdate_->graphics->fillRect(
        (int)(s.p.x + position.x / kStarsVelocitySlowDown) % width_,
        (int)(s.p.y + position.y / kStarsVelocitySlowDown) % height_, s.size, s.size,
        kColorWhite);
  });
}
