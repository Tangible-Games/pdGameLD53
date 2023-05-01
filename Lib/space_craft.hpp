#pragma once

#include "PdSymphony/all_symphony.hpp"
#include "camera.hpp"
#include "consts.hpp"
#include "pd_api.h"
#include "space_object.hpp"

using namespace PdSymphony::Math;

class SpaceStation;

class SpaceCraft : public SpaceObject {
 public:
  class Callback {
   public:
    virtual void OnHit(float impact) = 0;
  };

  SpaceCraft(PlaydateAPI* playdate)
      : playdate_(playdate),
        crank_prev_angle_(playdate->system->getCrankAngle()) {
    load();
  }

  void RegisterCallback(Callback* callback) { callback_ = callback; }

  void ResetSpaceStation(SpaceStation* space_station);

  void Start() { state_ = State::IN_GAME; }

  void Update(float dt);
  void Draw(const Camera& camera);
  void UpdateSounds();

  float GetSpeed() const { return velocity_.GetLength(); }

  void StartAligning(const Point2d& align_to) {
    playdate_->system->logToConsole("Switching to state: ALIGNING");
    state_ = State::ALIGNING;
    state_time_ = 0.0f;
    align_from_ = GetPosition();
    align_to_ = align_to;
    align_direction_from_ = direction_;
    velocity_ = Vector2d();
    engine_state_ = EngineState::IDLE;
    rotation_state_ = RotationState::IDLE;
  }

 private:
  void load();
  void updateInput(float dt);
  void updateMove(float dt);
  void updateAligning(float dt);
  void tryMove(const Vector2d& move);
  void draw(const Point2d& position);
  void drawDebug(const Point2d& position);

  static float getAngleBetweenAxisX(const Vector2d& v) {
    float a = acosf(v.x / v.GetLength());
    if (v.y < 0.0f) {
      return 2.0f * kPi - a;
    }
    return a;
  }

  static float getAngleBetween(const Vector2d& v1, const Vector2d& v2) {
    float a1 = getAngleBetweenAxisX(v1);
    float a2 = getAngleBetweenAxisX(v2);
    return a1 - a2;
  }

  enum class State { IN_GAME, ALIGNING, PARKED };

  enum class EngineState { IDLE, FLARE_UP, FORWARD, BACKWARD };

  enum class RotationState { IDLE, LEFT, RIGHT };

  enum class FieldState { IDLE, ACTIVE };

  PlaydateAPI* playdate_{nullptr};
  Callback* callback_{nullptr};
  SpaceStation* space_station_{nullptr};
  float radius_{kSpaceCraftRadius};
  Vector2d direction_{0.0f, -1.0f};
  float rotation_speed_deg_per_sec_{0.0f};
  float crank_prev_angle_{0.0f};

  State state_{State::IN_GAME};
  float state_time_{0.0f};
  Point2d align_from_;
  Point2d align_to_;
  Vector2d align_direction_from_;
  EngineState engine_state_{EngineState::IDLE};
  EngineState next_engine_state_{EngineState::IDLE};
  float engine_state_time_{0.0f};
  LCDBitmap* idle_bitmap_{nullptr};
  LCDBitmapTable* forward_bitmap_table_{nullptr};
  LCDBitmapTable* engine_left_up_bitmap_table_{nullptr};
  LCDBitmapTable* engine_left_down_bitmap_table_{nullptr};
  LCDBitmapTable* engine_right_up_bitmap_table_{nullptr};
  LCDBitmapTable* engine_right_down_bitmap_table_{nullptr};
  RotationState rotation_state_{RotationState::IDLE};
  float rotation_state_time_{0.0f};
  FieldState field_state_{FieldState::IDLE};
  float field_state_time_{0.0f};
  LCDBitmapTable* field_bitmap_table_{nullptr};
};
