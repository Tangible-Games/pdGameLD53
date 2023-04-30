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
  SpaceCraft(PlaydateAPI* playdate)
      : playdate_(playdate),
        crank_prev_angle_(playdate->system->getCrankAngle()) {
    load();
  }

  void ResetSpaceStation(SpaceStation* space_station);

  void Update(float dt);
  void Draw(const Camera& camera);

 private:
  void load();
  void updateInput(float dt);
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

  PlaydateAPI* playdate_{nullptr};
  SpaceStation* space_station_{nullptr};
  float radius_{20.0f};
  Vector2d direction_{0.0f, -1.0f};
  const float rotation_speed_deg_per_sec_{360.0f};
  float crank_prev_angle_{0.0f};

  LCDBitmap* idle_bitmap_{nullptr};
};
