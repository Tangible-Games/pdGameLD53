#pragma once

#include <stddef.h>

constexpr float kSpaceCraftPosX = 0.0f;
constexpr float kSpaceCraftPosY = 100.0f;
constexpr float kSpaceCraftAcceleration = 100.0f;
constexpr float kSpaceCraftVelocityMax = 1000.0f;
constexpr float kSpaceAsteroidHitVelocityReduction = 0.25f;

constexpr float kSpaceStationSize = 60.0f;

constexpr size_t kAsteroidsNum = 300;
constexpr size_t kAsteroidMinSize = 10;
constexpr size_t kAsteroidMaxSize = 30;
constexpr size_t kAsteroidToBaseAreaDistance = 300;
constexpr size_t kAsteroidAreaDistance = 2000;
constexpr size_t kAsteroidInitCollisionCheckNum = 3;

constexpr size_t kStarsNum = 20;
constexpr float kStarsVelocitySlowDown = 100.0f;
