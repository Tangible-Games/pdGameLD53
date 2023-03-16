#include "pd_api.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg) {
  playdate->system->logToConsole("Event handler.");
  return 0;
}
