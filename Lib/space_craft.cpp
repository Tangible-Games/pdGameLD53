#include "space_craft.hpp"

#include "space_station.hpp"

void SpaceCraft::ResetSpaceStation(SpaceStation* space_station) {
  space_station_ = space_station;
}

void SpaceCraft::Update(float dt) { updateInput(dt); }

void SpaceCraft::Draw(const Camera& camera) {
  drawDebug(camera.ConvertToCameraSpace(position_));
}

void SpaceCraft::updateInput(float dt) {
  PDButtons buttons_current;
  PDButtons buttons_pushed;
  PDButtons buttons_released;
  playdate_->system->getButtonState(&buttons_current, &buttons_pushed,
                                    &buttons_released);

  if (buttons_current & kButtonLeft) {
    float da = -rotation_speed_deg_per_sec_ * dt;
    direction_ = direction_.GetRotated(DegToRad(da));
  } else if (buttons_current & kButtonRight) {
    float da = rotation_speed_deg_per_sec_ * dt;
    direction_ = direction_.GetRotated(DegToRad(da));
  }

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
    velocity_ = velocity_ + direction_ * acceleration_ * dt;
    float v = velocity_.GetLength();
    if (v > max_linear_velocity_) {
      velocity_ = velocity_ * (max_linear_velocity_ / v);
    }
  }

  Vector2d move = velocity_ * dt;

  SpaceStation::CollisionData collision;
  space_station_->Collide(GetPosition(), radius_, move, collision);

  position_ = position_ + velocity_ * dt;
}

void SpaceCraft::drawDebug(const Point2d& position) {
  Point2d front = position + direction_ * 20.0f;
  Vector2d right_direction = direction_.GetRotated(DegToRad(-90.0f));
  Point2d right = position + right_direction * 10.0f - direction_ * 20.0f;
  Point2d left = position - right_direction * 10.0f - direction_ * 20.0f;
  playdate_->graphics->drawLine((int)front.x, (int)front.y, (int)right.x,
                                (int)right.y, 3, kColorBlack);
  playdate_->graphics->drawLine((int)right.x, (int)right.y, (int)left.x,
                                (int)left.y, 3, kColorBlack);
  playdate_->graphics->drawLine((int)left.x, (int)left.y, (int)front.x,
                                (int)front.y, 3, kColorBlack);

  playdate_->graphics->drawEllipse(
      (int)(position.x - radius_), (int)(position.y - radius_),
      (int)(radius_ * 2.0f), (int)(radius_ * 2.0f), 1, 0, 0, kColorBlack);
}
