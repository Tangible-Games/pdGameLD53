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
    if (players_[sample] == nullptr) {
      players_[sample] = playdate_->sound->sampleplayer->newPlayer();
      playdate_->sound->sampleplayer->setSample(players_[sample],
                                                sounds_[sample]);
    }
    if (players_[sample] &&
        !playdate_->sound->sampleplayer->isPlaying(players_[sample])) {
      playdate_->system->logToConsole("play: %d", sample);
      playdate_->sound->sampleplayer->play(players_[sample], 1.0, 1.0);
    }
  }

  void playStop(SoundSample sample) {
    if (players_[sample] &&
        playdate_->sound->sampleplayer->isPlaying(players_[sample])) {
      playdate_->system->logToConsole("play stop: %d", sample);
      playdate_->sound->sampleplayer->stop(players_[sample]);
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

  PlaydateAPI* playdate_{nullptr};

  std::array<AudioSample*, kSoundMax> sounds_;
  std::array<SamplePlayer*, kSoundMax> players_;
  FilePlayer* music_player_{nullptr};
  MusicSample music_current_{kMusicMax};
};
