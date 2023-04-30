#pragma once

#include <array>

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_api.h"
#include "space_object.hpp"

class Stars : public SpaceObject {
 public:
  Stars(PlaydateAPI* playdate)
      : playdate_(playdate),
        width_(playdate->display->getWidth()),
        height_(playdate->display->getHeight()) {}

  void Generate(uint32_t seed) {
    srand(seed);
    for (auto &s : stars_) {
      auto p = Point2d(rand() % width_, rand() % height_);
      s = Star(p, rand() % 4 + 1);
    }
  }

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void drawDebug(const Point2d& position);

  struct Star {
    Star() = default;

    Star(const Point2d& new_p, int new_size) : p(new_p), size(new_size) {}

    Point2d p;
    int size{1};
  };

  PlaydateAPI* playdate_{nullptr};
  int width_;
  int height_;
  std::array<Star, kStarsNum> stars_;
};
