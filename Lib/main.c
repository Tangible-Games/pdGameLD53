#include "PdSymphony/pd_system_helpers.h"
#include "game.h"
#include "pd_api.h"

static void *userdata = 0;

#ifdef _WINDLL
__declspec(dllexport)
#endif
    int eventHandler(PlaydateAPI *playdate, PDSystemEvent event, uint32_t arg) {
  (void)arg;
  playdate->system->logToConsole("#eventHandler, event: %s, arg: %i",
                                 PDSystemEventToString(event), arg);
  if (event == kEventInit) {
    playdate->display->setRefreshRate(50);

    userdata = SetupGame(playdate);
    playdate->system->setUpdateCallback(Update, userdata);
  }

  int result = 0;
  if (userdata) {
    EventHandler(userdata, event, arg);
  }
  return result;
}

#ifndef _WINDLL
void __attribute__((noreturn)) _exit(int status);
void __attribute__((noreturn)) _exit(int status) {
  (void)status;
  for (;;) {
  }
}

int _getpid(void);
int _getpid(void) { return 1; }

int _kill(int pid, int sig);
int _kill(int pid, int sig) {
  (void)pid;
  (void)sig;
  return -1;
}
#endif
