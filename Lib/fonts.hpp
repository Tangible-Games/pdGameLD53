#pragma once

#include "consts.hpp"
#include "pd_api.h"

class Fonts {
 public:
  static Fonts& instance() {
    static Fonts instances;
    return instances;
  }

  void loadFonts(PlaydateAPI* playdate) {
    const char* error = nullptr;
    // Load all fonts from consts.hpp kFontDataPath
    for (int i = 0; i < kFontLast; i++) {
      error = nullptr;
      fonts_[i] = playdate->graphics->loadFont(kFontDataPath[i], &error);
      if (error) {
        playdate->system->logToConsole("Failed to load font, error: %s", error);
      }
    }
  }

  LCDFont* use(FontName font) { return fonts_[font]; }

 private:
  Fonts() = default;

  std::array<LCDFont*, kFontLast> fonts_;
};
