#pragma once

namespace PdSymphony {
namespace Math {
const float kPi = 3.14159265f;

float DegToRad(float deg) { return deg * (kPi * 0.00555555555555f); }
}  // namespace Math
}  // namespace PdSymphony
