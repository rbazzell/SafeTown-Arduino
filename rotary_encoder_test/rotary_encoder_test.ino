#include <Encoder.h>

#define CLK 16
#define DT  17
#define SW  2
#define LED1 10
#define LED2 11
#define LED3 12

Encoder encoder;


long pos = -99;
long new_pos;

/*
void checkPosition() {
  encoder.tick();
}
*/

void setup() {
  /*
  attachInterrupt(digitalPinToInterrupt(CLK), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT ), checkPosition, CHANGE);
  */
  pinMode(SW, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  Serial.begin(115200);
  while(!Serial);
  encoder.attach(DT, CLK);

}

void loop() {
  new_pos = encoder.getPosition() / 2;
  if (new_pos != pos) {
    digitalWrite(LED3, HIGH);
    Serial.println(String(new_pos) + "  |  " + String(pos));
    if (new_pos > pos) {
      digitalWrite(LED2, HIGH);
    } else {
      digitalWrite(LED2, LOW);
    }
    pos = new_pos;
  }
  if (digitalRead(SW)) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED3, LOW);
  } else {
    digitalWrite(LED1, LOW);
  }
  delay(10);
}
