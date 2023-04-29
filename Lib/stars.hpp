#pragma once

#include <algorithm>
#include <vector>

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "pd_api.h"
#include "space_object.hpp"

class Stars : public SpaceObject {
 public:
  Stars(PlaydateAPI* playdate)
      : playdate_(playdate),
        width_(playdate->display->getWidth()),
        height_(playdate->display->getHeight()) {
    constexpr int num = 20;
    for (int i = 0; i < num; ++i) {
      auto p = Point2d(rand() % width_, rand() % height_);
      stars_.emplace_back(std::move(p));
    }
  }

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void drawDebug(const Point2d& position);

  PlaydateAPI* playdate_{nullptr};
  int width_;
  int height_;
  std::vector<Point2d> stars_;
};
