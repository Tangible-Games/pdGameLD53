#pragma once

#include <stddef.h>

#include <array>

#include "asteroid_type.hpp"
#include "game_state.hpp"
#include "mission_desc.hpp"

constexpr float kSpaceCraftRadius = 23.0f;
constexpr float kSpaceCraftPosX = 0.0f;
constexpr float kSpaceCraftPosY = 150.0f;
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
constexpr float kSpaceCraftToStationCameraOffset = 30.0f;
constexpr float kSpaceCraftToStationCameraOffsetRadius = 200.0f;
constexpr float kSpaceStationDockSpeed = 30.0f;
constexpr float kSpaceStationAlignTimeout = 2.0f;
constexpr int kSpaceStationDockingAnimationNumFrames = 19;
constexpr float kSpaceStationDockingAnimationLength = 1.9f;

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
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      0,
                      10,
                      1,
                      4,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          StationArea{
              .pos = Point2d(2 * 1000, 2 * 1000),
              .seed = 89127634,
              .name{"Station 2"},
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          StationArea{
              .pos = Point2d(-2 * 1000, 4 * 1000),
              .seed = 12847312,
              .name{"Station 3"},
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          StationArea{
              .pos = Point2d(-4 * 1000, -3 * 1000),
              .seed = 23098412,
              .name{"Station 4"},
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },

          StationArea{
              .pos = Point2d(-8 * 1000, 6 * 1000),
              .seed = 48120593,
              .name{"Falcon's Flight"},
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },

          StationArea{
              .pos = Point2d(10 * 1000, -9 * 1000),
              .seed = 37291048,
              .name{"Tardis Terminal"},
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },

          StationArea{
              .pos = Point2d(-6 * 1000, 5 * 1000),
              .seed = 28619075,
              .name{"Gallifrey Gateway"},
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },

          StationArea{
              .pos = Point2d(3 * 1000, -1 * 1000),
              .seed = 12938407,
              .name{"Stark Spaceport"},
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },

          StationArea{
              .pos = Point2d(9 * 1000, 8 * 1000),
              .seed = 54298103,
              .name{"Gotham Galactica"},
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },

          StationArea{
              .pos = Point2d(4 * 1000, -7 * 1000),
              .seed = 94057281,
              .name{"Metropolis Metastation"},
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },

          StationArea{
              .pos = Point2d(3 * 1000, 1 * 1000),
              .seed = 98214186,
              .name{"Station 5"},
              .desc{"Sehr gut station"},
              .num_asteroids =
                  {
                      50,
                      100,
                      150,
                      400,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          }};
}

inline std::vector<MissionDesc> GetMissions() {
  return {MissionDesc{
              .name{"Imported Space Coffee Beans"},
              .desc{"Aromatic and rich.\nKeep the cargo dry.\nCaffeine addicts "
                    "rejoice!"},
              .time_limit_str{"2 minutes"},
              .time_limit_sec = 120.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 600,
              .price_str{"5.000"},
              .price = 5000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Imported Space Coffee Beans 2"},
              .desc{"Aromatic and rich.\nKeep the cargo dry.\nCaffeine addicts "
                    "rejoice!"},
              .time_limit_str{"2 minutes"},
              .time_limit_sec = 120.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 600,
              .price_str{"5.000"},
              .price = 5000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          }};
}

constexpr size_t kStarsNum = 20;
constexpr float kStarsVelocitySlowDown = 100.0f;

constexpr int kUiArrowAnimationNumFrames = 8;
constexpr float kUiArrowAnimationLength = 1.6f;
constexpr int kUiClockAnimationNumFrames = 16;
constexpr float kUiClockAnimationLength = 1.0f;
constexpr bool kUiDrawSpeed = false;
constexpr float kUiMovingTooFastTimeout = 3.0f;

enum FontName {
  kFontBold = 0,
  kFontBoldOutlined,
  kFontBold2x,
  kFontLast,
};
constexpr const char* kFontDataPath[] = {
    // Source dir contains fnt(s) files and build system convert them to pft
    // files
    /* [kFontBold] = */ "data/fonts/Nontendo-Bold.pft",
    /* [kFontBoldOutlined] =  */ "data/fonts/Nontendo-Bold-Outlined.pft",
    /* [kFontBold2x] =  */ "data/fonts/Nontendo-Bold-2x.pft",
};

enum SoundSample {
  kSoundTrusters = 0,
  kSoundBackward,
  kSoundRotateLeft,
  kSoundRotateRight,
  kCollision1,
  kCollision2,
  kCollision3,
  kCollision4,
  kSoundMax
};
constexpr const char* kSoundsDataPath[] = {
    /* [kSoundTrusters] = */ "data/sounds/thruster.wav",
    /* [kSoundBackward] = */ "data/sounds/thruster_back.wav",
    /* [kSoundRotateLeft] = */ "data/sounds/rotate_left.wav",
    /* [kSoundRotateRight] = */ "data/sounds/rotate_right.wav",
    /* [kCollision1] = */ "data/sounds/collision-1.wav",
    /* [kCollision2] = */ "data/sounds/collision-2.wav",
    /* [kCollision3] = */ "data/sounds/collision-3.wav",
    /* [kCollision4] = */ "data/sounds/collision-4.wav",
};
constexpr float kSoundFadingDelta = 0.1f;

enum MusicSample { kMusicMain = 0, kMusicMax };
constexpr const char* kMusicDataPath[] = {
    /* [kMain] = */ "data/sounds/szegvari__space-bar-ambient.mp3",
};

constexpr bool kDrawDebugAsteroids = false;
constexpr bool kDrawDebugSpaceCraft = false;
constexpr bool kDrawDebugStation = false;
