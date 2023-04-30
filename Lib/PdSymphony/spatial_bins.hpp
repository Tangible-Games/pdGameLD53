#pragma once

#include "point2d.hpp"
#include "vector2d.hpp"

namespace PdSymphony {
namespace Collision {
template <typename ObjectType>
class SpatialBinsBase {
 public:
  void Remove(const ObjectType& object) {
    auto object_it = objects_.find(object);
    if (object_it != objects_.end()) {
      const auto& bins = (*object_it).second.bins;
      for (auto it = bins.begin(); it != bins.end(); ++it) {
        auto binIt = bins_.find((*it));
        if (binIt != bins_.end()) {
          (*binIt).second.objects.erase(object);
          if ((*binIt).second.objects.empty()) bins_.erase(binIt);
        }
      }

      objects_.erase(object_it);
    }
  }

 protected:
  typedef unsigned int HashType;

  void clear() {
    bins_.clear();
    objects_.clear();
  }

  void add(HashType spatial_hash, const ObjectType& object) {
    auto bin_pair = bins_.insert(std::make_pair(spatial_hash, Bin()));
    (*bin_pair.first).second.objects.insert(object);

    auto object_pair =
        objects_.insert(std::make_pair(object, InternalObject()));
    (*object_pair.first).second.bins.insert(spatial_hash);
  }

  void add(const std::vector<HashType>& spatial_hashes,
           const ObjectType& object) {
    for (size_t i = 0; i < spatial_hashes.size(); ++i) {
      add(spatial_hashes[i], object);
    }
  }

  std::set<ObjectType> query(
      const std::vector<HashType>& spatial_hashes) const {
    std::set<ObjectType> result;

    for (size_t i = 0; i < spatial_hashes.size(); ++i) {
      const HashType& spatial_hash = spatial_hashes[i];

      auto binIt = bins_.find(spatial_hash);
      if (binIt != bins_.end()) {
        const auto& objects = (*binIt).second.objects;
        for (auto object_it = objects.begin(); object_it != objects.end();
             ++object_it) {
          result.insert((*object_it));
        }
      }
    }

    return result;
  }

  static HashType hash(int i, int j) {
    unsigned int result = hashLy((unsigned char*)&i, sizeof(int));
    result = hashLy((unsigned char*)&j, sizeof(int), result);
    return result;
  }

  static HashType hash(int i, int j, int k) {
    unsigned int result = hashLy((unsigned char*)&i, sizeof(int));
    result = hashLy((unsigned char*)&j, sizeof(int), result);
    result = hashLy((unsigned char*)&k, sizeof(int), result);
    return result;
  }

  static unsigned int hashLy(const unsigned char* str, size_t length,
                             unsigned int start = 0) {
    unsigned int result = start;
    for (size_t i = 0; i < length; ++i) {
      result = (result * 1664525) + (*str) + 1013904223;
    }
    return result;
  }

 private:
  struct Bin {
    std::set<ObjectType> objects;
  };

  struct InternalObject {
    std::set<HashType> bins;
  };

  typedef std::unordered_map<HashType, Bin> Bins;
  typedef std::unordered_map<ObjectType, InternalObject> Objects;

  // spatial_hash->Bin
  Bins bins_;
  // object->InternalObject
  Objects objects_;
};

template <typename Type>
class SpatialBin2d : public SpatialBinBase<ObjectType> {
 public:
  SpatialBin2d() = default;

  SpatialBin2d(float cell_width, float cell_height)
      : cell_width_(cell_width), cell_height_(cell_height) {}

  void Clear() { SpatialBinBase<ObjectType>::clear(); }

  void Add(const Point2d& center, const Vector2d& half_sizes,
           const Type& object) {
    SpatialBinBase<ObjectType>::add(getBins(center, halfSizes), object);
  }

  std::set<ObjectType> Query(const Point2d& center,
                             const Vector2d& half_sizes) const {
    return SpatialBinBase<ObjectType>::query(getBins(center, half_sizes));
  }

 private:
  std::vector<typename SpatialBinBase<ObjectType>::HashType> getBins(
      const Point2d& center, const Vector2d& half_sizes) const {
    std::vector<typename SpatialBinBase<ObjectType>::HashType> result;

    int i_begin = 0;
    int i_end = 0;
    int j_begin = 0;
    int j_end = 0;
    rectCovers(center, half_sizes, cell_width_, cell_height_, i_begin, i_end,
               j_begin, j_end);

    result.reserve((i_end - i_begin) * (j_end - j_begin));
    for (int j = j_begin; j < j_end; ++j) {
      for (int i = i_begin; i < i_end; ++i) {
        result.push_back(symSpatialBin<Type>::hash(i, j));
      }
    }

    return result;
  }

  rectCovers(const Point2d& center, const Vector2d& half_sizes, cell_width,
             cell_height, int& i_begin_out, int& i_end_out, int& j_begin_out,
             int& j_end_out) {
    i_begin_out = 0;
    i_end_out = 0;
    j_begin_out = 0;
    j_end_out = 0;

    float left = center.x - half_sizes.x;
    float right = center.x + half_sizes.x;
    xBeginOut = fDiv(left, cell_width);
    xEndOut = fDiv(right, cell_width) + 1;

    float top = center.y + half_sizes.y;
    float bottom = center.y - half_sizes.y;
    yBeginOut = fDiv(bottom, cell_height);
    yEndOut = fDiv(top, cell_height) + 1;
  }

  int fDiv(float a, float b) {
    if (a < 0.0f) {
      return (int)(a / b) - 1;
    }
    return (int)(a / b);
  }

  float cell_width_{1.0f};
  float cell_height_{1.0f};
};
}  // namespace Collision
}  // namespace PdSymphony
