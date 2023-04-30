#pragma once

#include <stddef.h>

#include "point2d.hpp"
#include "vector2d.hpp"

namespace PdSymphony {
namespace Collision {
template <typename ObjectType>
class SpatialBin2d {
 public:
  SpatialBin2d() { buckets_.resize(1024); }

  SpatialBin2d(float cell_width, float cell_height, int num_buckets)
      : cell_width_(cell_width), cell_height_(cell_height) {
    buckets_.resize(num_buckets);
  }

  void Clear() {
    for (int i = 0; i < (int)buckets_.size(); ++i) {
      buckets_[i].objects.clear();
    }
  }

  void Add(const Math::Point2d& center, const Math::Vector2d& half_sizes,
           const ObjectType& object) {
    std::vector<uint32_t> buckets_hashes = getBucketsHashes(center, half_sizes);
    for (int i = 0; i < (int)buckets_hashes.size(); ++i) {
      int index = (int)(buckets_hashes[i] % buckets_.size());
      buckets_[index].objects.push_back(object);
    }
  }

  void Query(const Math::Point2d& center, const Math::Vector2d& half_sizes,
             std::vector<ObjectType>& result_out) const {
    result_out.clear();

    std::vector<uint32_t> buckets_hashes = getBucketsHashes(center, half_sizes);
    for (int i = 0; i < (int)buckets_hashes.size(); ++i) {
      int index = (int)(buckets_hashes[i] % buckets_.size());
      for (int j = 0; j < (int)buckets_[index].objects.size(); ++j) {
        const ObjectType& object = buckets_[index].objects[j];

        bool already_in_result = false;
        for (int k = 0; k < (int)result_out.size(); ++k) {
          if (object == result_out[k]) {
            already_in_result = true;
            break;
          }
        }

        if (!already_in_result) {
          result_out.push_back(buckets_[index].objects[j]);
        }
      }
    }
  }

  int GetMaxHashesCollision() const {
    int result = 0;
    for (int i = 0; i < (int)buckets_.size(); ++i) {
      if (result < (int)buckets_[i].objects.size()) {
        result = (int)buckets_[i].objects.size();
      }
    }
    return result;
  }

 private:
  static uint32_t hash(int i, int j) {
    uint32_t result = hashLy((unsigned char*)&i, sizeof(int));
    result = hashLy((unsigned char*)&j, sizeof(int), result);
    return result;
  }

  static uint32_t hashLy(const unsigned char* str, size_t length,
                         uint32_t start = 0) {
    uint32_t result = start;
    for (size_t i = 0; i < length; ++i) {
      result = (result * 1664525) + (*str) + 1013904223;
    }
    return result;
  }

  std::vector<uint32_t> getBucketsHashes(
      const Math::Point2d& center, const Math::Vector2d& half_sizes) const {
    std::vector<uint32_t> result;

    int i_begin = 0;
    int i_end = 0;
    int j_begin = 0;
    int j_end = 0;
    rectCovers(center, half_sizes, i_begin, i_end, j_begin, j_end);

    result.reserve((i_end - i_begin) * (j_end - j_begin));
    for (int j = j_begin; j < j_end; ++j) {
      for (int i = i_begin; i < i_end; ++i) {
        result.push_back(hash(i, j));
      }
    }

    return result;
  }

  void rectCovers(const Math::Point2d& center, const Math::Vector2d& half_sizes,
                  int& i_begin_out, int& i_end_out, int& j_begin_out,
                  int& j_end_out) const {
    i_begin_out = 0;
    i_end_out = 0;
    j_begin_out = 0;
    j_end_out = 0;

    float left = center.x - half_sizes.x;
    float right = center.x + half_sizes.x;
    i_begin_out = fDiv(left, cell_width_);
    i_end_out = fDiv(right, cell_width_) + 1;

    float bottom = center.y - half_sizes.y;
    float top = center.y + half_sizes.y;
    j_begin_out = fDiv(bottom, cell_height_);
    j_end_out = fDiv(top, cell_height_) + 1;
  }

  static int fDiv(float a, float b) {
    if (a < 0.0f) {
      return (int)(a / b) - 1;
    }
    return (int)(a / b);
  }

  struct Bucket {
    std::vector<ObjectType> objects;
  };

  float cell_width_{1.0f};
  float cell_height_{1.0f};
  std::vector<Bucket> buckets_;
};
}  // namespace Collision
}  // namespace PdSymphony
