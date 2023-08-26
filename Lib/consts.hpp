#pragma once

#include <stddef.h>

#include <array>

#include "asteroid_type.hpp"
#include "mission_desc.hpp"

constexpr float kSpaceCraftRadius = 23.0f;
constexpr float kSpaceCraftPosX = 0.0f;
constexpr float kSpaceCraftPosY = 1200.0f;
constexpr float kSpaceCraftAcceleration = 40.0f;
constexpr float kSpaceCraftDeceleration = 20.0f;
constexpr float kSpaceCraftVelocityMax = 80.0f;
constexpr float kSpaceCraftRotationAcceleration = 360.0f;  // Deg
constexpr float kSpaceCraftRotationSpeedMax = 180.0f;      // Deg
constexpr float kSpaceCraftRotationDeceleration = 180.0f;  // Deg
constexpr float kSpaceCraftAsteroidHitVelocityReduction = 0.2f;
constexpr float kSpaceCraftAsteroidHitRotationVelocityReduction = 0.15f;
constexpr bool kSpaceCraftCrankControlsRotation = false;
constexpr float kSpaceCraftFieldAnimationFps = 12.0f;
constexpr float kSpaceCraftForwardAnimationFps = 24.0f;
constexpr float kSpaceCraftForwardAnimationLoopingFrame = 2;
constexpr float kSpaceCraftSmallEnginesAnimationFps = 12.0f;
constexpr float kSpaceCraftCollisionBroadPhaseMargin = 20.0f;
constexpr float kSpaceCraftCollisionImpactToDamageBase = 10.0f;
constexpr float kSpaceCraftCollisionImpactToDamageRatio = 0.25f;
constexpr float kSpaceCraftDeliveryTimeFactor = 1.0f;
constexpr float kSpaceCraftDeliveryOutOfTimeFactor = 0.5f;
constexpr float kSpaceCraftHyperJumpAlignTimeout = 1.0f;
constexpr float kSpaceCraftHyperJumpCrankSpins = 360.0f * 3.0f;

constexpr float kSpaceStationRadius = 60.0f;
constexpr float kSpaceStationAnimationFps = 12.0f;
constexpr float kSpaceCraftToStationCameraOffset = 30.0f;
constexpr float kSpaceCraftToStationCameraOffsetRadius = 200.0f;
constexpr float kSpaceStationDockSpeed = 30.0f;
constexpr float kSpaceStationAlignTimeout = 2.0f;
constexpr float kSpaceStationDockingAnimationFps = 10.0f;
constexpr float kSpaceStationHyperJumpAnimationFps = 5.3f;
constexpr float kSpaceStationTakeOffRadius = 80.0f;

constexpr size_t kAsteroidInitCollisionCheckNum = 3;
constexpr float kAsteroidsSpatialBinsCellSize = 150.0f;
constexpr int kAsteroidsSpatialBinsSize = 1024;

inline std::vector<AsteroidType> GetAsteroidTypes() {
  // clang-format off
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
  // clang-format on
}

inline std::vector<MissionDesc> GetMissions() {
  // clang-format off
  return {MissionDesc{
              .name{"Imported Space Coffee Beans"},
              .desc{"Aromatic and rich.\nKeep the cargo dry.\nCaffeine addicts "
                    "rejoice!"},
              .time_limit_str{"3 minutes"},
              .time_limit_sec = 180.0f,
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
              .name{"Urgent Pizza Delivery"},
              .desc{"50 pizzas, 5 toppings each.\nPiping hot and ready to "
                    "eat.\nGet it there before it gets cold!"},
              .time_limit_str{"4 minutes"},
              .time_limit_sec = 240.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 600,
              .price_str{"3.500"},
              .price = 3500,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Enigmatic Alien Artifact"},
              .desc{"Precious, mysterious item.\nHandle with "
                    "care.\nDestination unknown."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 100,
              .price_str{"18.000"},
              .price = 18000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Live Band Equipment Haul"},
              .desc{"Drum set, guitars, lights.\nSetup tonight's concert.\nNo "
                    "scratches, please!"},
              .time_limit_str{"5 minutes"},
              .time_limit_sec = 300.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 700,
              .price_str{"4.000"},
              .price = 4000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Alien Diplomat Transport"},
              .desc{"High-ranking official going to Galactic\nsummit. Ensure a "
                    "smooth journey.\nSafety is a priority."},
              .time_limit_str{"6 minutes"},
              .time_limit_sec = 360.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 500,
              .price_str{"21.000"},
              .price = 21000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Rare Space Gemstone Cargo"},
              .desc{"Sparkling beauties within.\nDeliver without a "
                    "hitch.\nJewelers await."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 500,
              .price_str{"12.000"},
              .price = 12000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Zero-G Sports Gear Shipment"},
              .desc{"Basketballs, soccer balls.\nSpace sports "
                    "enthusiasts!\nDeliver on time."},
              .time_limit_str{"4 minutes"},
              .time_limit_sec = 240.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 900,
              .price_str{"3.500"},
              .price = 3500,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Wormhole Map Collection"},
              .desc{"Ancient, delicate scrolls.\nLost knowledge to be "
                    "found.\nHandle with great care."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 50,
              .price_str{"23.000"},
              .price = 23000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Interstellar Energy Drinks"},
              .desc{"1000 cans, various flavors.\nQuench the galaxy's "
                    "thirst.\nBe the speed of light!"},
              .time_limit_str{"3 minutes"},
              .time_limit_sec = 180.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 750,
              .price_str{"5.500"},
              .price = 5500,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Alien Floral Bouquets"},
              .desc{"Exotic blooms from afar.\nBring color to the "
                    "stars.\nFragile and rare."},
              .time_limit_str{"2 minutes"},
              .time_limit_sec = 120.0f,
              .cargo_durability_str{"ultra fragile"},
              .cargo_durability = 10,
              .price_str{"50.000"},
              .price = 50000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Fresh Moon Cheese Delivery"},
              .desc{"Aged to perfection.\nTaste buds will thank you.\nDon't "
                    "drop the cheese!"},
              .time_limit_str{"4 minutes"},
              .time_limit_sec = 240.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 400,
              .price_str{"6.000"},
              .price = 6000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Rocket Fuel Tanker Job"},
              .desc{"Highly flammable cargo.\nSteady hands required.\nProceed "
                    "with caution."},
              .time_limit_str{"3 minutes"},
              .time_limit_sec = 180.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 100,
              .price_str{"20.000"},
              .price = 20000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Space Fashion Show Attire"},
              .desc{"Trendy outfits from Earth.\nDress the stars, "
                    "literally.\nHandle with care."},
              .time_limit_str{"no limit"},
              .cargo_durability_str{"durable"},
              .cargo_durability = 200,
              .price_str{"7.000"},
              .price = 7000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Alien Craft Beer Delivery"},
              .desc{"100 barrels, best brews.\nKeep the cargo secure.\nBeer "
                    "enthusiasts await."},
              .time_limit_str{"6 minutes"},
              .time_limit_sec = 360.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 500,
              .price_str{"19.000"},
              .price = 19000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Space Mining Tools Shipment"},
              .desc{"Drills, lasers, explosives.\nEssential gear for "
                    "miners.\nDeliver in one piece."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 900,
              .price_str{"5.000"},
              .price = 5000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Vintage Sci-Fi Movie Props"},
              .desc{"Classic cinema history.\nPreserve the memories.\nTreat "
                    "them gently."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 100,
              .price_str{"10.000"},
              .price = 10000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Xenobiology Research Data"},
              .desc{"Critical findings onboard.\nScientific breakthroughs.\nNo "
                    "time to waste!"},
              .time_limit_str{"2 minutes"},
              .time_limit_sec = 120.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 10000,
              .price_str{"20.000"},
              .price = 20000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Robotic Chef Delivery"},
              .desc{"Culinary droids, 5 units.\nReady to cook up a "
                    "storm.\nHandle with care."},
              .time_limit_str{"3 minutes"},
              .time_limit_sec = 180.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 800,
              .price_str{"4.000"},
              .price = 4000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Luxury Space Yacht Parts"},
              .desc{"Deluxe, high-quality parts.\nCelestial cruisers "
                    "await.\nNo scratches allowed."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 800,
              .price_str{"10.000"},
              .price = 10000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Black Hole Exploration Kit"},
              .desc{"Advanced scientific gear.\nUnlock the mysteries.\nHandle "
                    "with precision."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 200,
              .price_str{"24.000"},
              .price = 24000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Wedding Dress from Earth"},
              .desc{"Elegant, delicate gown.\nA bride's dream come "
                    "true.\nPreserve the magic."},
              .time_limit_str{"4 minutes"},
              .time_limit_sec = 240.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 100,
              .price_str{"15.000"},
              .price = 15000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Alien Luxury Perfume Shipment"},
              .desc{"Exquisite scents of cosmos.\nBottle the essence of "
                    "stars.\nFragile glass bottles."},
              .time_limit_str{"6 minutes"},
              .time_limit_sec = 360.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 200,
              .price_str{"20.000"},
              .price = 20000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Alien Art Installation Pieces"},
              .desc{"Cosmic sculptures, paintings.\nDeliver beauty and "
                    "awe.\nTreat with reverence."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 150,
              .price_str{"19.000"},
              .price = 19000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Extraterrestrial Textbooks"},
              .desc{"Knowledge for young minds.\nExpand their "
                    "horizons.\nDeliver on time."},
              .time_limit_str{"5 minutes"},
              .time_limit_sec = 300.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 600,
              .price_str{"5.500"},
              .price = 5500,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Top Secret Spy Gadgets"},
              .desc{"Cutting-edge technology.\nFor your eyes only.\nKeep it "
                    "under wraps."},
              .time_limit_str{"6 minutes"},
              .time_limit_sec = 360.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 300,
              .price_str{"21.000"},
              .price = 21000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Organic Space Vegetable Run"},
              .desc{"Nutritious and delicious.\nFresh from the farm.\nKeep "
                    "them crisp."},
              .time_limit_str{"3 minutes"},
              .time_limit_sec = 180.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 900,
              .price_str{"3.500"},
              .price = 3500,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Holographic Home Decor"},
              .desc{"Futuristic furnishings.\nUpgrade living spaces.\nKeep "
                    "them in top shape."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 1000,
              .price_str{"2.000"},
              .price = 2000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Rare Space Animal Transport"},
              .desc{"Exotic, endangered species.\nHandle with love and "
                    "care.\nSafe travels required."},
              .time_limit_str{"6 minutes"},
              .time_limit_sec = 360.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 100,
              .price_str{"25.000"},
              .price = 25000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Classified Research Samples"},
              .desc{"Top-secret biological data.\nExtreme caution advised.\nNo "
                    "questions asked."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 100,
              .price_str{"10.000"},
              .price = 10000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Unstable Quark Containers"},
              .desc{"Highly sensitive cargo.\nPrecision handling "
                    "needed.\nProceed with caution."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"ultra fragile"},
              .cargo_durability = 1,
              .price_str{"50.000"},
              .price = 50000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Self-Replicating Nanobots"},
              .desc{"Advanced robotics tech.\nInfinite possibilities.\nContain "
                    "with care."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 150,
              .price_str{"15.000"},
              .price = 15000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Space Opera Sheet Music"},
              .desc{"Symphonies of the stars.\nTransport the sound of "
                    "space.\nKeep it in tune."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 10000,
              .price_str{"800"},
              .price = 800,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Designer Spacesuits Shipment"},
              .desc{"Fashion meets function.\nMake a statement in "
                    "space.\nCareful with the fabrics."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 600,
              .price_str{"1.000"},
              .price = 1000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Cryogenically Frozen Foods"},
              .desc{"Tasty treats, icy cold.\nPreserve the freshness.\nSpeedy "
                    "delivery needed."},
              .time_limit_str{"6 minutes"},
              .time_limit_sec = 360.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 400,
              .price_str{"12.000"},
              .price = 12000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Martian Microbrew Kegs"},
              .desc{"Bold flavors from Mars.\nQuench the thirst of many.\nKeep "
                    "it cold and steady."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 500,
              .price_str{"2.000"},
              .price = 2000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"FTL Engine Blueprints"},
              .desc{"Cutting-edge schematics.\nRevolutionize space "
                    "travel.\nKeep them secure."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 1000,
              .price_str{"5.000"},
              .price = 5000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Radioactive Isotope Samples"},
              .desc{"Hazardous materials.\nHandle with extreme care.\nSafety "
                    "first, always."},
              .time_limit_str{"5 minutes"},
              .time_limit_sec = 300.0f,
              .cargo_durability_str{"fragile"},
              .cargo_durability = 200,
              .price_str{"22.000"},
              .price = 22000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Intergalactic Poetry Books"},
              .desc{"Verse from across the cosmos.\nInspire the "
                    "imagination.\nDeliver the muse."},
              .time_limit_str{"no limit"},
              .time_limit_sec = 0.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 10000,
              .price_str{"1.500"},
              .price = 1500,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          MissionDesc{
              .name{"Diplomatic Peace Offerings"},
              .desc{"Gifts for alien leaders.\nForge new alliances.\nTreat "
                    "with respect."},
              .time_limit_str{"5 minutes"},
              .time_limit_sec = 240.0f,
              .cargo_durability_str{"durable"},
              .cargo_durability = 600,
              .price_str{"8.000"},
              .price = 8000,
              // Filled in code.
              .destination_str{""},
              .destination_index = -1,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          }};
  // clang-format on
}

constexpr size_t kStarsNum = 20;
constexpr float kStarsVelocitySlowDown = 100.0f;
constexpr float kStarsVelocitySlowDownHyperJump = 0.1f;

constexpr float kUiArrowAnimationFps = 12.0f;
constexpr float kUiClockAnimationFps = 12.0f;
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

enum MusicSample { kMusicMain = 0, kMusicBase, kMusicMax };
constexpr const char* kMusicDataPath[] = {
    /* [kMain] = */ "data/sounds/main_music.mp3",
    /* [kMusicBase] = */ "data/sounds/intro_music.mp3",
};

constexpr bool kDrawDebugAsteroids = false;
constexpr bool kDrawDebugSpaceCraft = false;
constexpr bool kDrawDebugStation = false;
