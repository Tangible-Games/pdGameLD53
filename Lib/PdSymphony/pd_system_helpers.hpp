#pragma once

#include "pd_api.h"

#ifdef __cplusplus
namespace PdSymphony {
namespace System {
#endif
const char* PDSystemEventToString(PDSystemEvent event) {
  const char* result = "";
  switch (event) {
    case kEventInit:
      result = "kEventInit";
      break;
    case kEventInitLua:
      result = "kEventInitLua";
      break;
    case kEventLock:
      result = "kEventLock";
      break;
    case kEventUnlock:
      result = "kEventUnlock";
      break;
    case kEventPause:
      result = "kEventPause";
      break;
    case kEventResume:
      result = "kEventResume";
      break;
    case kEventTerminate:
      result = "kEventTerminate";
      break;
    case kEventKeyPressed:
      result = "kEventKeyPressed";
      break;
    case kEventKeyReleased:
      result = "kEventKeyReleased";
      break;
    case kEventLowPower:
      result = "kEventLowPower";
      break;
  }
  return result;
}
#ifdef __cplusplus
}  // namespace System
}  // namespace PdSymphony
#endif
