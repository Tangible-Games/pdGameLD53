#include "space_craft.hpp"

#include "pd_helpers.hpp"
#include "sounds.hpp"
#include "space_station.hpp"

void SpaceCraft::ResetSpaceStation(SpaceStation* space_station) {
  space_station_ = space_station;
}

void SpaceCraft::Update(float dt) {
  if (state_ == State::IN_GAME) {
    updateInput(dt);
    updateMove(dt);
  } else if (state_ == State::PARKED) {
  } else if (state_ == State::ALIGNING) {
    updateAligning(dt);
  } else if (state_ == State::HYPER_JUMP) {
    updateHyperJump(dt);
  }

  forward_bitmap_animation_.Update(dt);
  engine_left_up_bitmap_animation_.Update(dt);
  engine_left_down_bitmap_animation_.Update(dt);
  engine_right_up_bitmap_animation_.Update(dt);
  engine_right_down_bitmap_animation_.Update(dt);
  field_bitmap_animation_.Update(dt);

  if (rotation_state_ != RotationState::IDLE) {
    rotation_state_time_ += dt;
  }

  if (field_state_ == FieldState::ACTIVE) {
    if (field_bitmap_animation_.IsIdle()) {
      field_state_ = FieldState::IDLE;
    }
  }
}

void SpaceCraft::Draw(const Camera& camera) {
  draw(camera.ConvertToCameraSpace(position_));
  if (kDrawDebugSpaceCraft) {
    drawDebug(camera.ConvertToCameraSpace(position_));
  }
}

void SpaceCraft::UpdateSounds() {
  switch (engine_state_) {
    case EngineState::IDLE:
      Sounds::instance().playStop(kSoundTrusters);
      Sounds::instance().playStop(kSoundBackward);
      break;

    case EngineState::FORWARD:
      Sounds::instance().play(kSoundTrusters);
      break;

    case EngineState::BACKWARD:
      Sounds::instance().play(kSoundBackward);
      break;
  }

  switch (rotation_state_) {
    case RotationState::IDLE:
      Sounds::instance().playStop(kSoundRotateLeft);
      Sounds::instance().playStop(kSoundRotateRight);
      break;

    case RotationState::LEFT:
      Sounds::instance().play(kSoundRotateLeft);
      break;

    case RotationState::RIGHT:
      Sounds::instance().play(kSoundRotateRight);
      break;
  }

  constexpr SoundSample sounds[] = {
      SoundSample::kCollision1, SoundSample::kCollision2,
      SoundSample::kCollision3, SoundSample::kCollision4};
  constexpr size_t collision_sounds_size = sizeof(sounds) / sizeof(sounds[0]);
  if (field_state_ == FieldState::ACTIVE) {
    int rand_collision = rand() % collision_sounds_size;
    Sounds::instance().play(sounds[rand_collision]);
  } else {
    for (size_t i = 0; i < collision_sounds_size; i++) {
      Sounds::instance().playStop(sounds[i]);
    }
  }
}

void SpaceCraft::load() {
  const char* error = nullptr;

  idle_bitmap_ = playdate_->graphics->loadBitmap("data/ship.png", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load ship's idle, error: %s",
                                    error);
  }

  LCDBitmapTable* bitmap_table =
      playdate_->graphics->loadBitmapTable("data/engine-forward.gif", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load ship's forward, error: %s",
                                    error);
  }
  forward_bitmap_animation_.Create(playdate_, bitmap_table,
                                   kSpaceCraftForwardAnimationFps);

  bitmap_table =
      playdate_->graphics->loadBitmapTable("data/engine-l-up.gif", &error);
  if (error) {
    playdate_->system->logToConsole(
        "Failed to load ship's engine left up, error: %s", error);
  }
  engine_left_up_bitmap_animation_.Create(playdate_, bitmap_table,
                                          kSpaceCraftSmallEnginesAnimationFps);

  bitmap_table =
      playdate_->graphics->loadBitmapTable("data/engine-l-dwn.gif", &error);
  if (error) {
    playdate_->system->logToConsole(
        "Failed to load ship's engine left down, error: %s", error);
  }
  engine_left_down_bitmap_animation_.Create(
      playdate_, bitmap_table, kSpaceCraftSmallEnginesAnimationFps);

  bitmap_table =
      playdate_->graphics->loadBitmapTable("data/engine-r-up.gif", &error);
  if (error) {
    playdate_->system->logToConsole(
        "Failed to load ship's engine right up, error: %s", error);
  }
  engine_right_up_bitmap_animation_.Create(playdate_, bitmap_table,
                                           kSpaceCraftSmallEnginesAnimationFps);

  bitmap_table =
      playdate_->graphics->loadBitmapTable("data/engine-r-dwn.gif", &error);
  if (error) {
    playdate_->system->logToConsole(
        "Failed to load ship's engine right down, error: %s", error);
  }
  engine_right_down_bitmap_animation_.Create(
      playdate_, bitmap_table, kSpaceCraftSmallEnginesAnimationFps);

  bitmap_table = playdate_->graphics->loadBitmapTable("data/field.gif", &error);
  if (error) {
    playdate_->system->logToConsole("Failed to load ship's field, error: %s",
                                    error);
  }
  field_bitmap_animation_.Create(playdate_, bitmap_table,
                                 kSpaceCraftFieldAnimationFps);
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

    if (rotation_state_ == RotationState::IDLE) {
      engine_left_down_bitmap_animation_.Play(/* looped= */ true);
      rotation_state_ = RotationState::LEFT;
      rotation_state_time_ = 0.0f;
    }
  } else if (buttons_current & kButtonRight) {
    rotation_speed_deg_per_sec_ =
        rotation_speed_deg_per_sec_ + kSpaceCraftRotationAcceleration * dt;
    if (rotation_speed_deg_per_sec_ > kSpaceCraftRotationSpeedMax) {
      rotation_speed_deg_per_sec_ = kSpaceCraftRotationSpeedMax;
    }

    if (rotation_state_ == RotationState::IDLE) {
      engine_right_down_bitmap_animation_.Play(/* looped= */ true);
      rotation_state_ = RotationState::RIGHT;
      rotation_state_time_ = 0.0f;
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

    engine_left_down_bitmap_animation_.Stop();
    engine_right_down_bitmap_animation_.Stop();
    rotation_state_ = RotationState::IDLE;
  }

  direction_ =
      direction_.GetRotated(DegToRad(rotation_speed_deg_per_sec_ * dt));

  if (kSpaceCraftCrankControlsRotation) {
    if (!playdate_->system->isCrankDocked()) {
      float crank_angle = playdate_->system->getCrankAngle();
      if (fabs(crank_angle - crank_prev_angle_) > 0.1f) {
        // When crank points towards top edge we assume that spacecraft should
        // face up.
        direction_ = Vector2d(0.0f, -1.0f).GetRotated(DegToRad(crank_angle));
      }
    }
  }

  crank_prev_angle_ = playdate_->system->getCrankAngle();

  bool update_velocity = false;
  if ((buttons_current & kButtonB) || (buttons_current & kButtonUp)) {
    velocity_ = velocity_ + direction_ * kSpaceCraftAcceleration * dt;
    update_velocity = true;

    if (engine_state_ == EngineState::IDLE) {
      PdAnimation::PlaybackParams playback_params;
      playback_params.looped = true;
      playback_params.looping_start_frame =
          kSpaceCraftForwardAnimationLoopingFrame;
      forward_bitmap_animation_.Play(playback_params);
      engine_state_ = EngineState::FORWARD;
      engine_state_time_ = 0.0f;
    }
  } else if ((buttons_current & kButtonA) || (buttons_current & kButtonDown)) {
    velocity_ = velocity_ - direction_ * kSpaceCraftDeceleration * dt;
    update_velocity = true;

    if (engine_state_ != EngineState::BACKWARD) {
      forward_bitmap_animation_.Stop();
      engine_left_up_bitmap_animation_.Play(/* looped= */ true);
      engine_right_up_bitmap_animation_.Play(/* looped= */ true);
      engine_state_ = EngineState::BACKWARD;
      engine_state_time_ = 0.0f;
    }
  }
  if (update_velocity) {
    float v = velocity_.GetLength();
    if (v > kSpaceCraftVelocityMax) {
      velocity_ = velocity_ * (kSpaceCraftVelocityMax / v);
    }
  } else {
    forward_bitmap_animation_.Stop();
    engine_state_ = EngineState::IDLE;
  }
}

void SpaceCraft::updateMove(float dt) {
  Vector2d move = velocity_ * dt;
  tryMove(move);
}

void SpaceCraft::updateAligning(float dt) {
  state_time_ += dt;
  float t = state_time_;
  if (state_time_ > kSpaceStationAlignTimeout) {
    playdate_->system->logToConsole("Switching to state: PARKED");
    state_ = State::PARKED;
    state_time_ = 0.0f;
    t = kSpaceStationAlignTimeout;
  }

  Vector2d move = (align_to_ - align_from_) * (t / kSpaceStationAlignTimeout);
  SetPosition(align_from_ + move);

  float angle = getAngleBetween(align_direction_from_, Vector2d(0.0f, -1.0f));
  float new_angle = angle * (1.0f - t / kSpaceStationAlignTimeout);
  direction_ = Vector2d(0.0f, -1.0f).GetRotated(new_angle);
}

void SpaceCraft::updateHyperJump(float dt) {
  state_time_ += dt;
  if (state_time_ > kSpaceCraftHyperJumpAlignTimeout) {
    state_time_ = kSpaceCraftHyperJumpAlignTimeout;
  }

  float angle = getAngleBetween(align_direction_from_, align_to_direction_);
  float new_angle = angle * (1.0f - state_time_ / kSpaceStationAlignTimeout);
  direction_ = align_to_direction_.GetRotated(new_angle);

  angle = getAngleBetween(align_velocity_from_, align_to_direction_);
  new_angle = angle * (1.0f - state_time_ / kSpaceStationAlignTimeout);
  velocity_ =
      (align_to_direction_ * velocity_.GetLength()).GetRotated(new_angle);

  // No collision.
  position_ = position_ + velocity_ * dt;
}

void SpaceCraft::tryMove(const Vector2d& move) {
  const auto& asteroids = space_station_->GetAsteroids();
  const SpatialBin2d<int>& asteroids_spatial_bin =
      space_station_->GetAsteroidsSpatialBin();

  position_ = position_ + move;

  Circle space_craft_circle(position_, radius_);

  std::vector<int> broad_phase;
  asteroids_spatial_bin.Query(
      position_,
      Vector2d(radius_ + kSpaceCraftCollisionBroadPhaseMargin,
               radius_ + kSpaceCraftCollisionBroadPhaseMargin),
      broad_phase);
  for (int broad_phase_i = 0; broad_phase_i < (int)broad_phase.size();
       ++broad_phase_i) {
    const auto& asteroid = asteroids[broad_phase[broad_phase_i]];

    Circle asteroid_circle(asteroid.GetPosition(), asteroid.GetRadius());
    if (asteroid_circle.Intersect(space_craft_circle)) {
      Vector2d out = (position_ - asteroid.GetPosition()).GetNormalized();
      position_ =
          asteroid.GetPosition() + out * (radius_ + asteroid.GetRadius());

      Vector2d tangent = out.GetRotated(DegToRad(-90.0f));

      float velocity_length = velocity_.GetLength();

      float x = out * velocity_;
      float y = tangent * velocity_;
      velocity_ =
          (out * (-x) + tangent * y) * kSpaceCraftAsteroidHitVelocityReduction;

      rotation_speed_deg_per_sec_ =
          rotation_speed_deg_per_sec_ *
          kSpaceCraftAsteroidHitRotationVelocityReduction;

      if (field_state_ != FieldState::ACTIVE) {
        field_bitmap_animation_.Play(/* looped */ false);
        field_state_ = FieldState::ACTIVE;
      }

      callback_->OnHit(velocity_length);
    }
  }
}

void SpaceCraft::draw(const Point2d& position) {
  float angle = getAngleBetween(direction_, Vector2d(0.0f, -1.0f));

  LCDBitmap* engine_bitmap = idle_bitmap_;
  LCDBitmap* small_engine_bitmap1 = nullptr;
  LCDBitmap* small_engine_bitmap2 = nullptr;
  LCDBitmap* small_engine_bitmap3 = nullptr;

  switch (engine_state_) {
    case EngineState::IDLE:
      engine_bitmap = idle_bitmap_;
      break;

    case EngineState::FORWARD:
      engine_bitmap = forward_bitmap_animation_.GetBitmap();
      break;

    case EngineState::BACKWARD:
      engine_bitmap = idle_bitmap_;
      small_engine_bitmap1 = engine_left_up_bitmap_animation_.GetBitmap();
      small_engine_bitmap2 = engine_right_up_bitmap_animation_.GetBitmap();
      break;
  }

  switch (rotation_state_) {
    case RotationState::IDLE:
      break;

    case RotationState::LEFT:
      small_engine_bitmap3 = engine_left_down_bitmap_animation_.GetBitmap();
      break;

    case RotationState::RIGHT:
      small_engine_bitmap3 = engine_right_down_bitmap_animation_.GetBitmap();
      break;
  }

  playdate_->graphics->drawRotatedBitmap(engine_bitmap, (int)position.x,
                                         (int)position.y, RadToDeg(angle), 0.5f,
                                         0.5f, 1.0f, 1.0f);
  if (small_engine_bitmap1) {
    playdate_->graphics->drawRotatedBitmap(
        small_engine_bitmap1, (int)position.x, (int)position.y, RadToDeg(angle),
        0.5f, 0.5f, 1.0f, 1.0f);
  }
  if (small_engine_bitmap2) {
    playdate_->graphics->drawRotatedBitmap(
        small_engine_bitmap2, (int)position.x, (int)position.y, RadToDeg(angle),
        0.5f, 0.5f, 1.0f, 1.0f);
  }
  if (small_engine_bitmap3) {
    playdate_->graphics->drawRotatedBitmap(
        small_engine_bitmap3, (int)position.x, (int)position.y, RadToDeg(angle),
        0.5f, 0.5f, 1.0f, 1.0f);
  }

  if (!field_bitmap_animation_.IsIdle()) {
    LCDBitmap* field_bitmap = field_bitmap_animation_.GetBitmap();
    DrawBitmapCentered(playdate_, field_bitmap, position);
  }
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
