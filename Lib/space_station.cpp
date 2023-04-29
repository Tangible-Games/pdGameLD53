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
        if (Circle(a.GetPosition(), a.GetRadius())
                .Intersect(Circle(asteroids_[j].GetPosition(),
                                  asteroids_[j].GetRadius()))) {
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

bool SpaceStation::circleCircleCCD(const Point2d& p1, float r1,
                                   const Vector2d& move, const Point2d& p2,
                                   float r2, float& move_factor_out) {
  Vector2d move_norm = move.GetNormalized();

  Vector2d to_circle = p2 - p1;

  float move_proj = to_circle * move_norm;
  if (move_proj < 0.0f) {
    return false;
  }

  Vector2d v = to_circle - move_norm * move_proj;
  float d = v.GetLength();
  if (d > (r1 + r2)) {
    return false;
  }

  float m = move_proj - sqrtf((r1 + r2) * (r1 + r2) - d * d);

  float move_length = move.GetLength();
  if (move_length < m) {
    return false;
  }

  move_factor_out = m / move_length;

  return true;
}
