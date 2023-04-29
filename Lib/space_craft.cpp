#include "space_craft.hpp"

void SpaceCraft::UpdateAndDraw(float dt, const Camera& camera) {
  updateInput(dt);
  drawDebug(camera.ConvertToCameraSpace(position_));
}

void SpaceCraft::updateInput(float dt) { (void)dt; }

void SpaceCraft::drawDebug(const Point2d& position) {
  int x = (int)position.x;
  int y = (int)position.y;
  playdate_->graphics->drawLine(x, y - 10, x, y + 10, 10, kColorBlack);
}
