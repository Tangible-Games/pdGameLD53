#pragma once

#include <stddef.h>

#include "asteroid_type.hpp"

constexpr float kSpaceCraftPosX = 0.0f;
constexpr float kSpaceCraftPosY = 100.0f;
constexpr float kSpaceCraftAcceleration = 100.0f;
constexpr float kSpaceCraftVelocityMax = 1000.0f;
constexpr float kSpaceCraftRotationAcceleration = 100.0f;  // Deg
constexpr float kSpaceCraftRotationSpeedMax = 100.0f;      // Deg
constexpr float kSpaceCraftRotationDeceleration = 100.0f;  // Deg
constexpr float kSpaceAsteroidHitVelocityReduction = 0.25f;
constexpr float kSpaceAsteroidHitRotationVelocityReduction = 0.25f;

constexpr float kSpaceStationSize = 60.0f;

constexpr size_t kAsteroidsNum = 300;
constexpr size_t kAsteroidMinSize = 10;
constexpr size_t kAsteroidMaxSize = 30;
constexpr size_t kAsteroidToBaseAreaDistance = 300;
constexpr size_t kAsteroidAreaDistance = 2000;
constexpr size_t kAsteroidInitCollisionCheckNum = 3;

inline std::vector<AsteroidType> GetAsteroidTypes() {
  return std::vector<AsteroidType>{{
                                       .models{"data/met_01.png"},
                                       .radius = 62.0f,
                                       .breaks_on_collision = false,
                                   },
                                   {
                                       .models{"data/met_02.png"},
                                       .radius = 48.0f,
                                       .breaks_on_collision = false,
                                   },
                                   {
                                       .models{"data/met_03.png"},
                                       .radius = 38.0f,
                                       .breaks_on_collision = false,
                                   },
                                   {
                                       .models{"data/met_04.png"},
                                       .radius = 23.0f,
                                       .breaks_on_collision = true,
                                   },
                                   {
                                       .models{"data/met_05.png"},
                                       .radius = 11.0f,
                                       .breaks_on_collision = true,
                                   }};
}

constexpr size_t kStarsNum = 20;
constexpr float kStarsVelocitySlowDown = 100.0f;
