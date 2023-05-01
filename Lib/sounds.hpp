#pragma once

#include "consts.hpp"
#include "pd_api.h"

class Sounds {
 public:
  static Sounds& instance() {
    static Sounds instances;
    return instances;
  }

  void setup(PlaydateAPI* playdate) { playdate_ = playdate; }

  void loadSounds() {
    // Load all Sounds from consts.hpp kSoundsDataPath
    for (int i = 0; i < kSoundMax; i++) {
      sounds_[i] = playdate_->sound->sample->load(kSoundsDataPath[i]);
    }
  }

  void play(SoundSample sample) {
    auto& player = players_[sample];
    if (player == nullptr) {
      player = playdate_->sound->sampleplayer->newPlayer();
      playdate_->sound->sampleplayer->setSample(player, sounds_[sample]);
    }
    if (player && !playdate_->sound->sampleplayer->isPlaying(player)) {
      playdate_->system->logToConsole("play: %d", sample);
      playdate_->sound->sampleplayer->play(player, 1.0, 1.0);
    }
    if (player && playdate_->sound->sampleplayer->isPlaying(player)) {
      // TODO: this can be optimized after the volume faded up.
      fading(player, FadingDir::Up);
    }
  }

  void playStop(SoundSample sample) {
    auto& player = players_[sample];
    if (player && playdate_->sound->sampleplayer->isPlaying(player)) {
      playdate_->system->logToConsole("play stop: %d", sample);
      auto level = fading(player, FadingDir::Down);
      if (level < 0.001f) {
        playdate_->sound->sampleplayer->stop(player);
      }
    }
  }

  void playMusic(MusicSample sample) {
    if (!music_player_) {
      music_player_ = playdate_->sound->fileplayer->newPlayer();
    }
    if (!music_player_) {
      return;
    }
    if (playdate_->sound->fileplayer->isPlaying(music_player_)) {
      playdate_->sound->fileplayer->stop(music_player_);
    }
    if (music_current_ != sample) {
      playdate_->sound->fileplayer->loadIntoPlayer(music_player_,
                                                   kMusicDataPath[sample]);
      music_current_ = sample;
    }
    playdate_->sound->fileplayer->play(music_player_, 0);
  }

  void stopMusic() {
    if (music_player_ &&
        playdate_->sound->fileplayer->isPlaying(music_player_)) {
      playdate_->sound->fileplayer->stop(music_player_);
    }
  }

 private:
  Sounds() = default;

  enum class FadingDir { Down, Up };
  float fading(SamplePlayer* player, FadingDir direction) {
    float left, right;
    playdate_->sound->sampleplayer->getVolume(player, &left, &right);
    switch (direction) {
      case FadingDir::Down:
        if (left > kSoundFadingDelta) {
          left -= kSoundFadingDelta;
          right -= kSoundFadingDelta;
        } else {
          left = right = 0.0f;
        }
        break;
      case FadingDir::Up:
        if (left < 1.0f - kSoundFadingDelta) {
          left += kSoundFadingDelta;
          right += kSoundFadingDelta;
        } else {
          left = right = 1.0f;
        }
        break;
    }
    playdate_->sound->sampleplayer->setVolume(player, left, right);
    return left;
  }

  PlaydateAPI* playdate_{nullptr};

  std::array<AudioSample*, kSoundMax> sounds_;
  std::array<SamplePlayer*, kSoundMax> players_;
  FilePlayer* music_player_{nullptr};
  MusicSample music_current_{kMusicMax};
};
