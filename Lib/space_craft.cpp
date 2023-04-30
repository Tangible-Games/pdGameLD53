#include "space_craft.hpp"

#include "space_station.hpp"

void SpaceCraft::ResetSpaceStation(SpaceStation* space_station) {
  space_station_ = space_station;
}

void SpaceCraft::Update(float dt) { updateInput(dt); }

void SpaceCraft::Draw(const Camera& camera) {
  draw(camera.ConvertToCameraSpace(position_));
  // drawDebug(camera.ConvertToCameraSpace(position_));
}

void SpaceCraft::load() {
  const char* error = 0;
  idle_bitmap_ = playdate_->graphics->loadBitmap("data/ship.png", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load ship idle, error: %s",
                                    error);
  }
}

void SpaceCraft::updateInput(float dt) {
  PDButtons buttons_current;
  PDButtons buttons_pushed;
  PDButtons buttons_released;
  playdate_->system->getButtonState(&buttons_current, &buttons_pushed,
                                    &buttons_released);

  if (buttons_current & kButtonLeft) {
    rotation_speed_deg_per_sec_ =
        rotation_speed_deg_per_sec_ - kSpaceCraftRotationAcceleration * dt;
    if (rotation_speed_deg_per_sec_ < -kSpaceCraftRotationSpeedMax) {
      rotation_speed_deg_per_sec_ = -kSpaceCraftRotationSpeedMax;
    }
  } else if (buttons_current & kButtonRight) {
    rotation_speed_deg_per_sec_ =
        rotation_speed_deg_per_sec_ + kSpaceCraftRotationAcceleration * dt;
    if (rotation_speed_deg_per_sec_ > kSpaceCraftRotationSpeedMax) {
      rotation_speed_deg_per_sec_ = kSpaceCraftRotationSpeedMax;
    }
  } else {
    if (rotation_speed_deg_per_sec_ < 0.0f) {
      rotation_speed_deg_per_sec_ =
          rotation_speed_deg_per_sec_ + kSpaceCraftRotationDeceleration * dt;
      if (rotation_speed_deg_per_sec_ > 0.0f) {
        rotation_speed_deg_per_sec_ = 0.0f;
      }
    } else if (rotation_speed_deg_per_sec_ > 0.0f) {
      rotation_speed_deg_per_sec_ =
          rotation_speed_deg_per_sec_ - kSpaceCraftRotationDeceleration * dt;
      if (rotation_speed_deg_per_sec_ < 0.0f) {
        rotation_speed_deg_per_sec_ = 0.0f;
      }
    }
  }

  direction_ =
      direction_.GetRotated(DegToRad(rotation_speed_deg_per_sec_ * dt));

  if (!playdate_->system->isCrankDocked()) {
    float crank_angle = playdate_->system->getCrankAngle();
    if (fabs(crank_angle - crank_prev_angle_) > 0.1f) {
      // When crank points towards top edge we assume that spacecraft should
      // face up.
      direction_ = Vector2d(0.0f, -1.0f).GetRotated(DegToRad(crank_angle));
    }
  }

  crank_prev_angle_ = playdate_->system->getCrankAngle();

  if ((buttons_current & kButtonB) || (buttons_current & kButtonUp)) {
    velocity_ = velocity_ + direction_ * kSpaceCraftAcceleration * dt;
    float v = velocity_.GetLength();
    if (v > kSpaceCraftVelocityMax) {
      velocity_ = velocity_ * (kSpaceCraftVelocityMax / v);
    }
  }

  Vector2d move = velocity_ * dt;
  tryMove(move);
}

void SpaceCraft::tryMove(const Vector2d& move) {
  const auto asteroids = space_station_->GetAsteroids();

  position_ = position_ + move;

  Circle space_craft_circle(position_, radius_);
  for (const auto asteroid : asteroids) {
    Circle asteroid_circle(asteroid.GetPosition(), asteroid.GetRadius());
    if (asteroid_circle.Intersect(space_craft_circle)) {
      Vector2d out = (position_ - asteroid.GetPosition()).GetNormalized();
      position_ =
          asteroid.GetPosition() + out * (radius_ + asteroid.GetRadius());

      Vector2d tangent = out.GetRotated(DegToRad(-90.0f));

      float x = out * velocity_;
      float y = tangent * velocity_;
      velocity_ =
          (out * (-x) + tangent * y) * kSpaceAsteroidHitVelocityReduction;
    }
  }
}

void SpaceCraft::draw(const Point2d& position) {
  float angle = getAngleBetween(direction_, Vector2d(0.0f, -1.0f));
  playdate_->graphics->drawRotatedBitmap(idle_bitmap_, (int)position.x,
                                         (int)position.y, RadToDeg(angle), 0.5f,
                                         0.5f, 1.0f, 1.0f);
}

void SpaceCraft::drawDebug(const Point2d& position) {
  Point2d front = position + direction_ * 20.0f;
  Vector2d right_direction = direction_.GetRotated(DegToRad(-90.0f));
  Point2d right = position + right_direction * 10.0f - direction_ * 20.0f;
  Point2d left = position - right_direction * 10.0f - direction_ * 20.0f;
  playdate_->graphics->drawLine((int)front.x, (int)front.y, (int)right.x,
                                (int)right.y, 3, kColorWhite);
  playdate_->graphics->drawLine((int)right.x, (int)right.y, (int)left.x,
                                (int)left.y, 3, kColorWhite);
  playdate_->graphics->drawLine((int)left.x, (int)left.y, (int)front.x,
                                (int)front.y, 3, kColorWhite);

  playdate_->graphics->drawEllipse(
      (int)(position.x - radius_), (int)(position.y - radius_),
      (int)(radius_ * 2.0f), (int)(radius_ * 2.0f), 1, 0, 0, kColorWhite);
}
