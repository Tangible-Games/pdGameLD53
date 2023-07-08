#include "space_stations_descs.hpp"

SpaceStationDesc GetST01CentralStationDesc();
SpaceStationDesc GetST99TestDesc();

const std::vector<SpaceStationDesc>& GetSpaceStationsDescs() {
  bool initialized = false;
  static std::vector<SpaceStationDesc> descs;

  if (!initialized) {
    descs.push_back(GetST01CentralStationDesc());
    descs.push_back(GetST99TestDesc());
    initialized = true;
  }

  return descs;
}
