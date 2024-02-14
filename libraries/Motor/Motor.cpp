#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int pinA, int pinB) {
  _pinA = pinA;
  _pinB = pinB;
}

void Motor::begin() {
  pinMode(_pinA, OUTPUT);
  pinMode(_pinB, OUTPUT);
}

void Motor::forward(int speed) {
  analogWrite(_pinA, 255 - speed);
  digitalWrite(_pinB, HIGH);
}

void Motor::reverse(int speed) {
  digitalWrite(_pinA, HIGH);
  analogWrite(_pinB, 255 - speed);
}

void Motor::brake() {
  digitalWrite(_pinA, HIGH);
  digitalWrite(_pinB, HIGH);
}

void Motor::neutral() {
  digitalWrite(_pinA, LOW);
  digitalWrite(_pinB, LOW);
}
