#pragma once

#include <stddef.h>

#include <array>

#include "asteroid_type.hpp"
#include "game_state.hpp"
#include "mission_desc.hpp"

constexpr float kSpaceCraftRadius = 23.0f;
constexpr float kSpaceCraftPosX = 0.0f;
constexpr float kSpaceCraftPosY = 1000.0f;
constexpr float kSpaceCraftAcceleration = 40.0f;
constexpr float kSpaceCraftDeceleration = 15.0f;
constexpr float kSpaceCraftVelocityMax = 80.0f;
constexpr float kSpaceCraftRotationAcceleration = 360.0f;  // Deg
constexpr float kSpaceCraftRotationSpeedMax = 180.0f;      // Deg
constexpr float kSpaceCraftRotationDeceleration = 180.0f;  // Deg
constexpr float kSpaceCraftAsteroidHitVelocityReduction = 0.2f;
constexpr float kSpaceCraftAsteroidHitRotationVelocityReduction = 0.15f;
constexpr bool kSpaceCraftCrankControlsRotation = false;
constexpr float kSpaceCraftFieldAnimationLength = 0.5f;
constexpr int kSpaceCraftFieldAnimationNumFrames = 5;
constexpr float kSpaceCraftForwardAnimationLength = 0.25f;
constexpr int kSpaceCraftForwardAnimationNumFrames = 6;
constexpr int kSpaceCraftForwardAnimationSeqStart = 2;
constexpr int kSpaceCraftForwardAnimationSeqLength = 3;
constexpr int kSpaceCraftFlareUpAnimationSeqStart = 0;
constexpr int kSpaceCraftFlareUpAnimationSeqLength = 2;
constexpr float kSpaceCraftSmallEnginesAnimationLenght = 0.25f;
constexpr float kSpaceCraftSmallEnginesAnimationNumFrames = 3;
constexpr float kSpaceCraftCollisionBroadPhaseMargin = 20.0f;

constexpr float kSpaceStationRadius = 60.0f;
constexpr float kSpaceStationAnimationNumFrames = 2.4f;
constexpr float kSpaceStationAnimationLength = 2.4f;
constexpr float kSpaceCraftToStationCameraOffset = 50.0f;
constexpr float kSpaceCraftToStationCameraOffsetRadius = 200.0f;

constexpr size_t kAsteroidInitCollisionCheckNum = 3;
constexpr float kAsteroidsSpatialBinsCellSize = 150.0f;
constexpr int kAsteroidsSpatialBinsSize = 1024;

inline std::vector<AsteroidType> GetAsteroidTypes() {
  return std::vector<AsteroidType>{{
                                       .models{"data/met_01.png"},
                                       .bitmaps{},
                                       .radius = 61.0f,
                                       .breaks_on_collision = false,
                                   },
                                   {
                                       .models{"data/met_02.png"},
                                       .bitmaps{},
                                       .radius = 47.0f,
                                       .breaks_on_collision = false,
                                   },
                                   {
                                       .models{"data/met_03.png"},
                                       .bitmaps{},
                                       .radius = 37.0f,
                                       .breaks_on_collision = false,
                                   },
                                   {
                                       .models{"data/met_04.png"},
                                       .bitmaps{},
                                       .radius = 22.0f,
                                       .breaks_on_collision = true,
                                   },
                                   {
                                       .models{"data/met_05.png"},
                                       .bitmaps{},
                                       .radius = 10.0f,
                                       .breaks_on_collision = true,
                                   }};
}

inline std::vector<StationArea> GetStations() {
  return {StationArea{
              .pos = Point2d(0, 0),
              .seed = 13124125,
              .name{"Station 1"},
              .num_asteroids =
                  {
                      0,
                      10,
                      1,
                      4,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
          },
          StationArea{
              .pos = Point2d(2 * 1000, 2 * 1000),
              .seed = 89127634,
              .name{"Station 2"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
          },
          StationArea{
              .pos = Point2d(-2 * 1000, 4 * 1000),
              .seed = 12847312,
              .name{"Station 3"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
          },
          StationArea{
              .pos = Point2d(-4 * 1000, -3 * 1000),
              .seed = 23098412,
              .name{"Station 4"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
          },
          StationArea{
              .pos = Point2d(3 * 1000, 1 * 1000),
              .seed = 98214186,
              .name{"Station 5"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
          }};
}

inline std::vector<MissionDesc> GetMissions() { return {MissionDesc{}}; }

constexpr size_t kStarsNum = 20;
constexpr float kStarsVelocitySlowDown = 100.0f;

constexpr int kUiArrowAnimationNumFrames = 8;
constexpr float kUiArrowAnimationLength = 1.6f;
constexpr int kUiClockAnimationNumFrames = 16;
constexpr float kUiClockAnimationLength = 1.0f;

enum {
  kFontBold = 0,
  kFontBoldOutlined,
  kFontLast,
};
constexpr const char* kFontDataPath[] = {
    // Source dir contains fnt(s) files and build system convert them to pft
    // files
    /* [kFontBold] = */ "data/fonts/Nontendo-Bold.pft",
    /* [kFontBoldOutlined] =  */ "data/fonts/Nontendo-Bold-Outlined.pft",
};

constexpr bool kDrawDebugAsteroids = false;
constexpr bool kDrawDebugSpaceCraft = false;
constexpr bool kDrawDebugStation = false;
