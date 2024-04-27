#include <Music.h>

#define SPEAKER 13 
Music music(13);


void setup() {
  Serial.begin(9600);
  while(!Serial);
  music.begin();
  music.loadTestSong();
}

void loop() {
  music.playSong();
}