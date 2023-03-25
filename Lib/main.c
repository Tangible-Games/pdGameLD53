#include "game.h"
#include "pd_api.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif
    int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg) {
  playdate->system->logToConsole("Event handler");
  if (event == kEventInit) {
    playdate->display->setRefreshRate(50);

    void* userdata = SetupGame(playdate);
    playdate->system->setUpdateCallback(Update, userdata);
  }
  return 0;
}
