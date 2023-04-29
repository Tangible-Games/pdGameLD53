#include "space_station.hpp"

#include <algorithm>

void SpaceStation::Update(float dt) {
  std::for_each(asteroids_.begin(), asteroids_.end(),
                [dt](auto& a) { a.Update(dt); });
}

void SpaceStation::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));

  std::for_each(asteroids_.begin(), asteroids_.end(),
                [&](auto& a) { a.Draw(camera); });
}

void SpaceStation::Collide(const Point2d& p, float r, const Vector2d& move,
                           CollisionData& collision_out) const {
  (void)p;
  (void)r;
  (void)move;
  (void)collision_out;
}

void SpaceStation::drawDebug(const Point2d& position) {
  playdate_->graphics->drawLine((int)position.x - kSpaceStationSize / 2,
                                (int)position.y - kSpaceStationSize / 2,
                                (int)position.x + kSpaceStationSize / 2,
                                (int)position.y - kSpaceStationSize / 2, 3,
                                kColorBlack);
  playdate_->graphics->drawLine((int)position.x + kSpaceStationSize / 2,
                                (int)position.y - kSpaceStationSize / 2,
                                (int)position.x + kSpaceStationSize / 2,
                                (int)position.y + kSpaceStationSize / 2, 3,
                                kColorBlack);
  playdate_->graphics->drawLine((int)position.x + kSpaceStationSize / 2,
                                (int)position.y + kSpaceStationSize / 2,
                                (int)position.x - kSpaceStationSize / 2,
                                (int)position.y + kSpaceStationSize / 2, 3,
                                kColorBlack);
  playdate_->graphics->drawLine((int)position.x - kSpaceStationSize / 2,
                                (int)position.y + kSpaceStationSize / 2,
                                (int)position.x - kSpaceStationSize / 2,
                                (int)position.y - kSpaceStationSize / 2, 3,
                                kColorBlack);
}

void SpaceStation::createAsteroids() {
  for (size_t i = 0; i < kAsteroidsNum; ++i) {
    // random size 10,20,30
    float radius = (float)(kAsteroidMinSize *
                           (1 + rand() % kAsteroidMaxSize / kAsteroidMinSize));
    Asteroid a(playdate_, radius);

    for (size_t k = 0; k < kAsteroidInitCollisionCheckNum; ++k) {
      // random possition
      auto distance =
          kAsteroidToBaseAreaDistance + rand() % kAsteroidAreaDistance;
      auto angle = DegToRad(rand() % 360);
      a.SetPosition(Point2d(distance * cos(angle), distance * sin(angle)));

      bool intersects = false;
      for (size_t j = 0; j < asteroids_.size(); ++j) {
        if (intersectCircles(a.GetPosition(), a.GetRadius(),
                             asteroids_[j].GetPosition(),
                             asteroids_[j].GetRadius())) {
          intersects = true;
          break;
        }
      }

      if (!intersects) {
        break;
      }
    }

    asteroids_.emplace_back(std::move(a));
  }
}

bool SpaceStation::intersectCircles(const Point2d& p1, float r1,
                                    const Point2d& p2, float r2) {
  Vector2d v = p2 - p1;
  if (v.GetLength() > (r1 + r2)) {
    return false;
  }
  return true;
}
