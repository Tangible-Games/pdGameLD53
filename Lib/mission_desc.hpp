#pragma once

#include <string>

struct MissionDesc {
  std::string name;
  std::string desc;
  std::string time_limit_str;
  float time_limit_sec{0.0f};
  std::string cargo_durability_str;
  int cargo_durability{0};
  std::string price_str;
  int price{};
  std::string destination_str;
  int destination_index{0};
  std::string difficulty_str;
  int difficulty{0};
};
