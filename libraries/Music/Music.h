#ifndef Music_h
#define Music_h

#define G2  100
#define Gs2 104
#define Ab2 Gs2
#define A2  110
#define As2 117
#define Bb2 As2
#define B2  124
#define C3  131
#define Cs3 139
#define Db3 Cs3
#define D3  147
#define Ds3 156
#define Eb3 Ds3
#define E3  165
#define F3 	175 
#define Fs3 185
#define Gb3 Fs3
#define G3  196
#define Gs3 208
#define Ab3 Gs3
#define A3  220
#define As3 233
#define Bb3 As3
#define B3  247
#define C4  262
#define Cs4 277
#define Db4 Cs4
#define D4  294
#define Ds4 311
#define Eb4 Ds4
#define E4  330
#define F4  349
#define Fs4 370
#define Gb4 Fs4
#define G4  392
#define Gs4 415
#define Ab4 Gs4
#define A4  440
#define As4 466
#define Bb4 As4

//static int test_notes[17] = {G2,  G2,  D3,  Bb2, Bb2, Bb2, F3,  0,   C3,  C3,  C3,  D3,  Eb3, 0,   D3,  Bb2, A2 };
//static int test_duras[17] = {450, 150, 300, 300, 450, 150, 300, 300, 450, 150, 300, 300, 300, 300, 300, 150, 150};

const int MAX_SONG_LENGTH = 512;

static int test_notes_arr[67] = {0,   F4,  E4,  D4,  C4,  D4,  C4,  A3,  Bb3, 0,   Bb3, C4,  Bb3, A3,  Bb3, 0,   C4, 
                             0,   F4,  E4,  D4,  C4,  D4,  C4,  A3,  C4,  G4,  A4,  0,   A4,  G4,  F4,
                             0,   F4,  E4,  D4,  C4,  D4,  C4,  A3,  Bb3, 0,   Bb3, C4,  Bb3, A3,  Bb3, 0,   C4,
                             0,   A4,  G4,  G4,  F4,  F4,  E4,  F4,  E4,  D4,  0,   F4,  F4,  G4,  F4,  G4,  A4,  0};
static int test_duras_arr[67] = {150, 450, 300, 300, 300, 300, 150, 300, 150, 150, 450, 300, 300, 150, 150, 150, 750,
                             150, 450, 300, 300, 300, 300, 150, 300, 750, 450, 150, 150, 150, 300, 600,
                             150, 450, 300, 300, 300, 300, 150, 300, 150, 150, 450, 300, 300, 150, 150, 150, 750,
                             150, 450, 300, 300, 300, 300, 150, 150, 150, 150, 900, 300, 300, 150, 150, 300, 300, 900};


#include "Arduino.h"
#include "Vector.h"

static int* durationToTiming(int *durations, Vector<int> *timings, int length) {
  int t[length + 1] = {0};
  timings = t;
  timings[0] = 0;
  for (int i = 0; i < length; i++) {
    timings[i + 1] = timings[i] + durations[i];
    Serial.println(String(timings[i + 1]) + " = " + String(timings[i]) + " + " + String(durations[i]));
  }
  timings[0] = timings[length];
  return timings;
}

class Music {
  public:
    Music(int pin);
    void begin();
    void setVolume(int volume);
    void play(int note_freq);
    void rest();
    void reset();
    void playSong();
    void loopSong();
    void loadSong(int* notes, int* durations, int length);
    void loadTestSong();
  private:
    int _pin;
	  int _volume;
    int _songi;   
    unsigned long _songStart;
    int _playing;
    volatile int* _notes;
    volatile int* _durations;
    int strg_arr[MAX_SONG_LENGTH];
    volatile Vector<int> _timings(strg_arr);
};

#endif