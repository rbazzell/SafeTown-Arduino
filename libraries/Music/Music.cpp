#include "Arduino.h"
#include "Music.h"
#include "Vector.h"

Music::Music(int pin) {
  _pin = pin;
  _volume = 50;
  _songi = 0;
  _playing = 0; //0 is hasn't played, 1 is playing, and 2 is played
}

void Music::begin() {
  pinMode(_pin, OUTPUT);
  _songStart = millis();
}

void Music::setVolume(int volume) {
	_volume = volume;
}

void Music::play(int note_freq) {
	analogWriteFreq(note_freq);
	analogWrite(_pin, _volume);
}

void Music::rest() {
  analogWrite(_pin, 0);
}

void Music::reset() {
  _songi = 0;
  _songStart = millis();
  _playing = 0;
}

void Music::playSong() {
  switch (_playing) {
    case 0:
      for (int i = 0; i <= 3; i ++) {
        Serial.println(String(_timings[i]));
      }
      reset();
      _playing = 2;
      break;
    case 1:
      Serial.print(String(millis()) + "  " + String(_timings[_songi + 1]) + "      ");
      if(millis() > _timings[0] + _songStart) {
        Serial.println("END");
        _playing = 2;
        rest();
      } else if(millis() > _timings[_songi + 1] + _songStart) {
          _songi++;
      } else if (millis() > _timings[_songi + 1] - 15 + _songStart) {
          rest();
      } else {
          Serial.println("PLAYING   " + String(_songi));
          play(_notes[_songi]);
      }
      break;
    case 2:
      rest();
      break;
  }

}

void Music::loopSong() {
  playSong();
  if (_playing == 2) {
    _playing = 0;
  }
}

void Music::loadSong(int* notes, int* durations, int length) {
  reset();
  _notes = notes;
  _durations = durations;
  int t[length + 1] = {0};
  _timings = t;
  for (int i = 0; i < length; i++) {
    _timings[i + 1] = _timings[i] + _durations[i];
  }
  _timings[0] = _timings[length];
}

void Music::loadTestSong() {
  loadSong(test_notes, test_duras, 67);
}