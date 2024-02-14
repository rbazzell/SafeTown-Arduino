#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
const int t = 5;
class Motor {
  public:
    Motor(int pinA, int pinB);
    void begin();
    void forward(int speed);
    void reverse(int speed);
    void brake();
    void neutral();
  private:
    int _pinA, _pinB;
    
};

#endif