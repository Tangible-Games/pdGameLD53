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

void SpaceStation::drawDebug(const Point2d& position) {
  playdate_->graphics->drawLine((int)position.x - spaceStationSize / 2,
                                (int)position.y - spaceStationSize / 2,
                                (int)position.x + spaceStationSize / 2,
                                (int)position.y - spaceStationSize / 2, 3,
                                kColorBlack);
  playdate_->graphics->drawLine((int)position.x + spaceStationSize / 2,
                                (int)position.y - spaceStationSize / 2,
                                (int)position.x + spaceStationSize / 2,
                                (int)position.y + spaceStationSize / 2, 3,
                                kColorBlack);
  playdate_->graphics->drawLine((int)position.x + spaceStationSize / 2,
                                (int)position.y + spaceStationSize / 2,
                                (int)position.x - spaceStationSize / 2,
                                (int)position.y + spaceStationSize / 2, 3,
                                kColorBlack);
  playdate_->graphics->drawLine((int)position.x - spaceStationSize / 2,
                                (int)position.y + spaceStationSize / 2,
                                (int)position.x - spaceStationSize / 2,
                                (int)position.y - spaceStationSize / 2, 3,
                                kColorBlack);
}

void SpaceStation::createAsteroids() {
  for (size_t i = 0; i < asteroidsNum; ++i) {
    // random size 10,20,30
    float radius = (float)(asteroidMinSize *
                           (1 + rand() % asteroidMaxSize / asteroidMinSize));
    Asteroid a(playdate_, radius);

    for (size_t k = 0; k < asteroidInitCollisionCheckNum; ++k) {
      // random possition
      auto distance =
          asteroidToBaseAreaDistance + rand() % asteroidAreaDistance;
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
