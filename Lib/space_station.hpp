#pragma once

#include <vector>

#include "PdSymphony/all_symphony.hpp"
#include "asteroid.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_api.h"
#include "space_object.hpp"

class SpaceStation : public SpaceObject {
 public:
  SpaceStation(PlaydateAPI* playdate) : playdate_(playdate) {
    createAsteroids();
  }

  void Update(float dt);
  void Draw(const Camera& camera);

  struct CollisionData {
    bool has_collision{false};
    bool hits_space_station{false};
    float move_factor{1.0f};
  };

  void Collide(const Point2d& p, float r, const Vector2d& move,
               CollisionData& collision_out) const;

 private:
  void drawDebug(const Point2d& position);
  void createAsteroids();

  static bool intersectCircles(const Point2d& p1, float r1, const Point2d& p2,
                               float r2);

  PlaydateAPI* playdate_{nullptr};

  std::vector<Asteroid> asteroids_;
};
