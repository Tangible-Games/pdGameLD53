#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "asteroid_type.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_api.h"
#include "space_object.hpp"

class Asteroid : public SpaceObject {
 public:
  Asteroid(PlaydateAPI* playdate, const AsteroidType& type)
      : playdate_(playdate), type_(&type) {
    bitmap_index_ = rand() % type_->bitmaps.size();
  }

  float GetRadius() const { return type_->radius; }

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void draw(const Point2d& position);
  void drawDebug(const Point2d& position);

  PlaydateAPI* playdate_{nullptr};
  const AsteroidType* type_{nullptr};
  int bitmap_index_{0};
};
