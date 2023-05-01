#pragma once

#include <stddef.h>

#include <array>

#include "asteroid_type.hpp"
#include "game_state.hpp"
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
constexpr float kSpaceCraftCollisionImpactToDamageBase = 10.0f;
constexpr float kSpaceCraftCollisionImpactToDamageRatio = 0.25f;
constexpr float kSpaceCraftDeliveryTimeFactor = 1.0f;
constexpr float kSpaceCraftDeliveryOutOfTimeFactor = 0.5f;

constexpr float kSpaceStationRadius = 60.0f;
constexpr float kSpaceStationAnimationNumFrames = 2.4f;
constexpr float kSpaceStationAnimationLength = 2.4f;
constexpr float kSpaceCraftToStationCameraOffset = 30.0f;
constexpr float kSpaceCraftToStationCameraOffsetRadius = 200.0f;
constexpr float kSpaceStationDockSpeed = 30.0f;
constexpr float kSpaceStationAlignTimeout = 2.0f;
constexpr int kSpaceStationDockingAnimationNumFrames = 19;
constexpr float kSpaceStationDockingAnimationLength = 1.9f;
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

inline std::vector<StationArea> GetStations() {
  // clang-format off
  return {StationArea{
              .pos = Point2d(0, 0),
              .seed = 13124130,
              .name{"Central Station"},
              .desc{"Guten Tag, Hola, Hello!\nWelcome to Central!\nTravellers, "
                    "businessmen and diplomats just\nlove visiting. Feel at "
                    "home here and\nmake sure to come back once in a while"},
              .num_asteroids =
                  {
                      0,
                      10,
                      15,
                      18,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 1500.0f,
              .jump_distance = 1800.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          StationArea{
              .pos = Point2d(2 * 1000, 2 * 1000),
              .seed = 13124125,
              .name{"Central Station 2"},
              .desc{"Guten Tag, Hola, Hello!\nWelcome to Central!\nTravellers, "
                    "businessmen and diplomats just\nlove visiting. Feel at "
                    "home here and\nmake sure to come back once in a while"},
              .num_asteroids =
                  {
                      0,
                      10,
                      1,
                      4,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 1500.0f,
              .jump_distance = 1800.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          StationArea{
              .pos = Point2d(2 * 1000, 2 * 1000),
              .seed = 89127634,
              .name{"Infinity Junction"},
              .desc{"Needless to say, there are quite a few\nworlds connected "
                    "via this station.\nMaybe your homeworld is one of them?"},
              .num_asteroids =
                  {
                      50,
                      100,
                      100,
                      200,
                      50,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 2000.0f,
              .jump_distance = 2300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
          },
          StationArea{
              .pos = Point2d(-2 * 1000, 4 * 1000),
              .seed = 12847312,
              .name{"Celestial Crossroads"},
              .desc{"Enigmatic name and stale tasteless beer.\nSadly, there is "
                    "nothing more here.\nA trading outpost with a meager "
                    "population\nof 172 as of today. Wait, 171."},
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
              .name{"Big Rock"},
              .desc{"Lovers of big rocks live here.\nArtists, sculptors, "
                    "businessmen\nYou into big rocks yourself?"},
              .num_asteroids =
                  {
                      370,
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
              .desc{"A bustling hub for smugglers,\nexplorers, and pilots with "
                    "a\nneed for speed."},
              .num_asteroids =
                  {
                      100,
                      100,
                      150,
                      200,
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
              .name{"Gagarin's Gate"},
              .desc{"Honoring the first human in\nspace, this station "
                    "celebrates\nspace exploration history."},
              .num_asteroids =
                  {
                      0,
                      200,
                      200,
                      0,
                      100,
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
              .name{"Interstellar Inn"},
              .desc{"A cozy rest stop for weary\ncosmic travelers, "
                    "offering\nwarm beds and hot meals."},
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
              .name{"Tardis Terminal"},
              .desc{"A hub for time travelers and\nDoctor Who fans. Catch a "
                    "ride\nthrough space and time!"},
              .num_asteroids =
                  {
                      50,
                      150,
                      250,
                      200,
                      100,
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
              .desc{"The only interesting thing about\nthis crime-ridden hole "
                    "in the end\nof nowhere is the bat-like light\n shining on "
                    "the nearby asteroids."},
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
              .name{"Asgard Anchorage"},
              .desc{"Viking heritage and Norse\nmythology enthusiasts "
                    "unite.\nWelcome to Valhalla!"},
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
              .pos = Point2d(-5 * 1000, -4 * 1000),
              .seed = 93210487,
              .name{"Deneb Dock"},
              .desc{"Star gazers and astronomers\nflock to this station for "
                    "its\namazing views of Deneb."},
              .num_asteroids =
                  {
                      100,
                      150,
                      100,
                      100,
                      100,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 2500.0f,
              .jump_distance = 2800.0f,
              .difficulty_str{"difficult"},
              .difficulty = 2,
          },

          StationArea{
              .pos = Point2d(1 * 1000, -1 * 1000),
              .seed = 28193740,
              .name{"Eridani Enclave"},
              .desc{"A scientific hub, researching\nthe Eridani star system "
                    "and its\npotential for life."},
              .num_asteroids =
                  {
                      200,
                      150,
                      100,
                      50,
                      50,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 2500.0f,
              .jump_distance = 2800.0f,
              .difficulty_str{"difficult"},
              .difficulty = 2,
          },

          StationArea{
              .pos = Point2d(6 * 1000, 8 * 1000),
              .seed = 71628934,
              .name{"Fomalhaut Fort"},
              .desc{"A fortified station at the edge\nof the Fomalhaut "
                    "system,\nprotecting its secrets."},
              .num_asteroids =
                  {
                      100,
                      300,
                      50,
                      100,
                      50,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 2500.0f,
              .jump_distance = 2800.0f,
              .difficulty_str{"difficult"},
              .difficulty = 2,
          },

          StationArea{
              .pos = Point2d(7 * 1000, -3 * 1000),
              .seed = 85213047,
              .name{"Gacrux Gateway"},
              .desc{"This gateway serves as a\nlaunchpad for expeditions "
                    "to\nthe Gacrux star."},
              .num_asteroids =
                  {
                      50,
                      100,
                      80,
                      100,
                      100,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 2500.0f,
              .jump_distance = 2800.0f,
              .difficulty_str{"moderate"},
              .difficulty = 2,
          },

          StationArea{
              .pos = Point2d(8 * 1000, 2 * 1000),
              .seed = 17903482,
              .name{"Martian Metropolis"},
              .desc{"A thriving city on Mars,\nshowcasing human\ningenuity and "
                    "persistence."},
              .num_asteroids =
                  {
                      50,
                      50,
                      70,
                      100,
                      200,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 2700.0f,
              .jump_distance = 3000.0f,
              .difficulty_str{"easy"},
              .difficulty = 0,
          },

          StationArea{
              .pos = Point2d(2 * 1000, 3 * 1000),
              .seed = 37819420,
              .name{"Neptunian Nook"},
              .desc{"A chilly station on the edge\nof the solar system, for "
                    "those\nwho enjoy the cold."},
              .num_asteroids =
                  {
                      50,
                      50,
                      70,
                      100,
                      200,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 2700.0f,
              .jump_distance = 3000.0f,
              .difficulty_str{"easy"},
              .difficulty = 0,
          },

          StationArea{
              .pos = Point2d(-3 * 1000, 5 * 1000),
              .seed = 92183074,
              .name{"Orion's Observatory"},
              .desc{"A space station with stunning\nviews of the Orion Nebula "
                    "and\nits star-forming regions."},
              .num_asteroids =
                  {
                      50,
                      50,
                      70,
                      100,
                      200,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 2700.0f,
              .jump_distance = 3000.0f,
              .difficulty_str{"easy"},
              .difficulty = 0,
          },

          StationArea{
              .pos = Point2d(10 * 1000, 6 * 1000),
              .seed = 23819045,
              .name{"Jovian Junction"},
              .desc{"A hub for gas giant\nenthusiasts and "
                    "researchers,\nexploring Jupiter-like worlds."},
              .num_asteroids =
                  {
                      50,
                      50,
                      70,
                      100,
                      200,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 2700.0f,
              .jump_distance = 3000.0f,
              .difficulty_str{"easy"},
              .difficulty = 0,
          },

          StationArea{
              .pos = Point2d(-1 * 1000, -6 * 1000),
              .seed = 49628103,
              .name{"Odin's Outpost"},
              .desc{"Wise and mighty warriors gather\nat this station, seeking "
                    "Odin's\ncounsel and mead."},
              .num_asteroids =
                  {
                      100,
                      100,
                      150,
                      150,
                      100,
                  },
              .asteroids_to_base_distance = 200.0f,
              .asteroids_area_distance = 3000.0f,
              .jump_distance = 3300.0f,
              .difficulty_str{"moderate"},
              .difficulty = 1,
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
              .name{"Urgent Holographic Pizza Delivery"},
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

enum MusicSample { kMusicMain = 0, KMusicIntro, kMusicMax };
constexpr const char* kMusicDataPath[] = {
    /* [kMain] = */ "data/sounds/main_music.mp3",
    /* [KMusicIntro] = */ "data/sounds/intro_music.mp3",
};

constexpr bool kDrawDebugAsteroids = false;
constexpr bool kDrawDebugSpaceCraft = false;
constexpr bool kDrawDebugStation = false;
