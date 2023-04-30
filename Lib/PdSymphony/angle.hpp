#pragma once

namespace PdSymphony {
namespace Math {
const float kPi = 3.14159265f;
const float kPiInv = 1.0f / kPi;

inline float DegToRad(float deg) { return deg * (kPi * 0.00555555555555f); }

inline float RadToDeg(float rad) { return rad * (180.0f * kPiInv); }
}  // namespace Math
}  // namespace PdSymphony
