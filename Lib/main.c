#include "game.h"
#include "pd_api.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif
    int eventHandler(PlaydateAPI *playdate, PDSystemEvent event, uint32_t arg) {
  (void)arg;
  playdate->system->logToConsole("Event handler");
  if (event == kEventInit) {
    playdate->display->setRefreshRate(50);

    void *userdata = SetupGame(playdate);
    playdate->system->setUpdateCallback(Update, userdata);
  }
  return 0;
}

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
