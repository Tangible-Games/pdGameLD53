#pragma once

#include <vector>

#include "angle.hpp"
#include "point2d.hpp"

namespace PdSymphony {
namespace Visibility {

class RayCastingProjection {
 public:
  RayCastingProjection() { SetViewport(400, 240, 90.0f); }

  RayCastingProjection(int screen_width, int screen_height,
                       float horizontal_fov_deg) {
    SetViewport(screen_width, screen_height, horizontal_fov_deg);
  }

  void SetViewport(int screen_width, int screen_height,
                   float horizontal_fov_deg) {
    screen_width_ = screen_width;
    screen_height_ = screen_height;
    aspect_ratio_ = (float)screen_width / (float)screen_height;
    horizontal_half_fov_deg_ = horizontal_fov_deg / 2.0f;
    horizontal_half_fov_tan_ = tanf(Math::DegToRad(horizontal_half_fov_deg_));
    rebuildRayDeltas();
  }

  void SetCamera(const Math::Point2d& origin, float origin_z,
                 const Math::Vector2d& camera_direction_norm) {
    camera_origin_ = origin;
    camera_z_ = origin_z;
    camera_direction_norm_ = camera_direction_norm;
    camera_right_norm_ =
        camera_direction_norm_.GetRotated(Math::DegToRad(-90.0f));
  }

  /// \arg p Point to project in world space.
  Math::Point2d Project(const Math::Point2d& p, float p_z) {
    Math::Vector2d to_p = p - camera_origin_;
    float dx = to_p * camera_right_norm_;
    float dy = to_p * camera_direction_norm_;
    float dz = p_z - camera_z_;
    float screen_x = dx / (horizontal_half_fov_tan_ * dy);
    float screen_y = dz * aspect_ratio_ / (horizontal_half_fov_tan_ * dy);
    return Math::Point2d(screen_x, screen_y);
  }

  /// \arg v Ray vector in camera space.
  /// \arg d Distance along vector v to point to project.
  /// \arg p_z z coordinate of the point to project in world space.
  Math::Point2d Project(const Math::Vector2d& v_norm, float d, float p_z) {
    float dx = v_norm.x * d;
    float dy = v_norm.y * d;
    float dz = p_z - camera_z_;
    float screen_x = dx / (horizontal_half_fov_tan_ * dy);
    float screen_y = dz * aspect_ratio_ / (horizontal_half_fov_tan_ * dy);
    return Math::Point2d(screen_x, screen_y);
  }

  Math::Vector2d GetRayWorld(int ray_index) const {
    int screen_half_width = screen_width_ / 2;
    float X = 1 / horizontal_half_fov_tan_;
    float x =
        ((float)(ray_index - screen_half_width) / (float)screen_half_width) * X;
    return (camera_right_norm_ * x + camera_direction_norm_) *
           ray_lengths_inv_[ray_index];
  }

  Math::Point2d Project(int ray_index, float d, float p_z) {
    float dx = rays_[ray_index].x * d;
    float dy = rays_[ray_index].y * d;
    float dz = p_z - camera_z_;
    float screen_x = dx / (horizontal_half_fov_tan_ * dy);
    float screen_y = dz * aspect_ratio_ / (horizontal_half_fov_tan_ * dy);
    return Math::Point2d(screen_x, screen_y);
  }

 private:
  void rebuildRayDeltas() {
    // TODO(truvorskameikin): Build rays only for the half of the screen to save
    // some memory.

    int screen_half_width = screen_width_ / 2;
    float X = 1 / horizontal_half_fov_tan_;

    rays_.resize(screen_width_);
    ray_lengths_inv_.resize(screen_width_);
    for (int i = 0; i < screen_width_; ++i) {
      float x = ((float)(i - screen_half_width) / (float)screen_half_width) * X;
      Math::Vector2d v = Math::Vector2d(x, 1.0f);

      ray_lengths_inv_[i] = 1.0f / v.GetLength();
      rays_[i] = Math::Vector2d(x, 1.0f).GetNormalized();
    }
  }

  float screen_width_{400};
  float screen_height_{240};
  float aspect_ratio_{400.0f / 240.0f};
  float horizontal_half_fov_deg_{45.0f};
  float horizontal_half_fov_tan_{tanf(Math::DegToRad(45.0f))};
  std::vector<Math::Vector2d> rays_;
  std::vector<float> ray_lengths_inv_;
  Math::Point2d camera_origin_;
  float camera_z_{0.0f};
  Math::Vector2d camera_direction_norm_;
  Math::Vector2d camera_right_norm_;
};

}  // namespace Visibility
}  // namespace PdSymphony
