#include <Servo.h>
#include <Motor.h>

#define OUTSIDE_MAX 3700
#define INSIDE_MAX  3700
#define ASYMPTOTE   20
#define DIFF_MIN    -2400
#define DIFF_MAX    2450

#define STOP     2
#define START    3
#define DISP_SDA 4
#define DISP_SCL 5
#define LEFT_A   6
#define LEFT_B   7
#define RIGHT_A  8
#define RIGHT_B  9
#define RED      10
#define GREEN    11
#define YELLOW   12
#define BUZZER   13
#define SERVO    14
#define ENC_A    15
#define ENC_B    16
#define ENC_S    17
#define BRAKE    23
#define TURN_L   24
#define TURN_R   25 //also BUILTIN_LED
#define IR_F     26
#define IR_I     27
#define IR_O     28
#define IR_D     29

Servo steer;
long pos;
const int turn_rad = 60;
const int center = 106;

int inside, outside;
long correction;

bool go_nstop = false;

Motor left(LEFT_A, LEFT_B);
Motor right(RIGHT_A, RIGHT_B);
int speed = 75; 

void setup() {
  pinMode(IR_I, INPUT);
  pinMode(IR_O, INPUT);

  pinMode(START, INPUT_PULLUP);
  pinMode(STOP, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(START), startISR, RISING);
  attachInterrupt(digitalPinToInterrupt(STOP), haltISR, RISING);

  steer.attach(SERVO);

  left.begin();
  right.begin();
}

void loop() {
  while (go_nstop) {
    inside = analogRead(IR_I);
    outside = analogRead(IR_O);
    correction = outside - inside;
    /*if (correction > 650) {
      intersection(inside, outside, 0);
    }
    else {
      lineFollow(inside, outside, correction);
    }*/
    lineFollow(inside, outside, correction);
  }
  left.brake();
  right.brake();
  steer.write(center);
}

void haltISR() {
  go_nstop = false;
}

void startISR() {
  go_nstop = true;
}

void lineFollow(int inside, int outside, long correction) {
  if (inside < INSIDE_MAX - 20 && outside >  OUTSIDE_MAX - 20 && correction > ASYMPTOTE + 20) {
    pos = center - turn_rad;
  } else if (outside < OUTSIDE_MAX - 20 && inside > INSIDE_MAX - 20 && correction < ASYMPTOTE - 20) {
    pos = center + turn_rad;
  } else {
    pos = map(correction, DIFF_MIN + 1500, DIFF_MAX - 1500, center - turn_rad, center + turn_rad);
  }
  steer.write(pos);
  left.forward(speed);
  right.forward(speed);
}

void intersection(int inside, int outside, int direction) {
  while(go_nstop && inside > INSIDE_MAX - 20 && outside > OUTSIDE_MAX - 20) {
    switch(direction) {
      case 1: //right turn
        left.forward(speed);
        right.forward(speed);
        steer.write(center + 45);
      case 2: //left turn
        left.forward(speed);
        right.forward(speed);
        steer.write(center - 30);
      default:
        left.forward(speed);
        right.forward(speed);
        steer.write(center);
        break;
    }
  }
}
