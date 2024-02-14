#include <Motor.h>
#include <Servo.h>

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

enum class test_state: uint8_t {
  LIGHTS        = 0,
  DEBUG_LEDS    = 1,
  DEBUG_BUZZER  = 2,
  ENCODER_SERVO = 3,
  LEFT_MOTOR    = 4,
  RIGHT_MOTOR   = 5,
  FRONT_IR      = 6,
  INSIDE_IR     = 7,
  OUTSIDE_IR    = 8,
  DOWN_IR       = 9
};


Servo servo;
Motor left(LEFT_A, LEFT_B);
Motor right(RIGHT_A, RIGHT_B);

test_state state = test_state::LIGHTS;

void setup() {
  //initialize servo and motors
  Serial.begin(9600);
  while(!Serial);
  servo.attach(SERVO);
  servo.write(90);
  left.begin(); 
  left.brake();
  right.begin();
  right.brake();

  //initialize outputs
  pinMode(RED,    OUTPUT);
  pinMode(GREEN,  OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BRAKE,  OUTPUT);
  pinMode(TURN_L, OUTPUT);
  pinMode(TURN_R, OUTPUT);

  //initialize inputs
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);
  pinMode(ENC_S, INPUT);
  pinMode(STOP,  INPUT);
  pinMode(START, INPUT);
  pinMode(IR_F,  INPUT);
  pinMode(IR_I,  INPUT);
  pinMode(IR_O,  INPUT);
  pinMode(IR_D,  INPUT);
  attachInterrupt(digitalPinToInterrupt(START), backISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(STOP), forwardISR, FALLING);
}

void backISR() {
  state = (test_state)(((int)state - 1) % 10);
  resetAll();
}

void forwardISR() {
  state = (test_state)(((int)state + 1) % 10);
  resetAll();
}

void loop() {
  test_state curr_state = state;
  switch (curr_state) {
    case test_state::LIGHTS:
      digitalWrite(TURN_L, HIGH);
      digitalWrite(TURN_R, HIGH);
      digitalWrite(BRAKE, HIGH);
      break;
    case test_state::DEBUG_LEDS:
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(YELLOW, HIGH);
      break;
    case test_state::DEBUG_BUZZER:
      digitalWrite(BUZZER, HIGH);
      break;
    case test_state::ENCODER_SERVO:
      servo.write(140);
      break;
    case test_state::LEFT_MOTOR:
      left.forward(127);
      break;
    case test_state::RIGHT_MOTOR:
      right.forward(127);
      break;
    case test_state::FRONT_IR:
      Serial.println("Front IR: " + String(analogRead(IR_F)));
      break;
    case test_state::INSIDE_IR:
      Serial.println("Inside IR: " + String(analogRead(IR_I)));
      break;
    case test_state::OUTSIDE_IR:
      Serial.println("Outside IR: " + String(analogRead(IR_O)));
      break;
    case test_state::DOWN_IR:
      Serial.println("Down IR: " + String(analogRead(IR_D)));
      break;
    default:
      break;
  }
  delay(5);
  if(curr_state != state) {
    resetAll();
  }
}

void resetAll() {
  servo.write(90);
  left.brake();
  right.brake();
  digitalWrite(RED,    LOW);
  digitalWrite(GREEN,  LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(BUZZER, LOW);
  digitalWrite(BRAKE,  LOW);
  digitalWrite(TURN_L, LOW);
  digitalWrite(TURN_R, LOW);
}