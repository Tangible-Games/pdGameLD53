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

  void play(SoundSample sample) {
    // playdate_->system->logToConsole("play: %d", sample);
    auto& player = players_[sample];
    if (player == nullptr) {
      sounds_[sample] = playdate_->sound->sample->load(kSoundsDataPath[sample]);
      player = playdate_->sound->sampleplayer->newPlayer();
      playdate_->sound->sampleplayer->setSample(player, sounds_[sample]);
    }
    if (player && !playdate_->sound->sampleplayer->isPlaying(player)) {
      playdate_->sound->sampleplayer->play(player, 1.0, 1.0);
    }
    if (player && playdate_->sound->sampleplayer->isPlaying(player)) {
      fading(player, FadingDir::Up);
    }
  }

  void playStop(SoundSample sample) {
    // playdate_->system->logToConsole("play stop: %d", sample);
    auto& player = players_[sample];
    if (player && playdate_->sound->sampleplayer->isPlaying(player)) {
      auto level = fading(player, FadingDir::Down);
      if (level < 0.001f) {
        playdate_->sound->sampleplayer->stop(player);
        playdate_->sound->sampleplayer->freePlayer(player);
        player = nullptr;
        playdate_->sound->sample->freeSample(sounds_[sample]);
        sounds_[sample] = nullptr;
      }
    }
  }

  void playMusic(MusicSample sample) {
    // playdate_->system->logToConsole("play music: %d", sample);
    if (music_player_ &&
        playdate_->sound->fileplayer->isPlaying(music_player_)) {
      if (music_current_ == sample) {
        return;
      } else {
        stopMusic();
      }
    }
    if (!music_player_) {
      music_player_ = playdate_->sound->fileplayer->newPlayer();
      if (!music_player_) {
        return;
      }
    }
    playdate_->sound->fileplayer->loadIntoPlayer(music_player_,
                                                 kMusicDataPath[sample]);
    music_current_ = sample;

    playdate_->sound->fileplayer->play(music_player_, 0);
  }

  void stopMusic() {
    if (music_player_ &&
        playdate_->sound->fileplayer->isPlaying(music_player_)) {
      playdate_->sound->fileplayer->stop(music_player_);
      playdate_->sound->fileplayer->freePlayer(music_player_);
      music_player_ = nullptr;
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
