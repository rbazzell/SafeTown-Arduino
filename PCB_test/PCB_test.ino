#include <Motor.h>
//#include <Music.h>
#include <Servo.h>
#include <Encoder.h>
#include <DisplayOurValues.h>

#define STOP     17
#define START    16
#define DISP_SDA 4
#define DISP_SCL 5
#define LEFT_A   24
#define LEFT_B   23
#define RIGHT_A  22
#define RIGHT_B  21
#define RED      10
#define GREEN    11
#define YELLOW   12
#define BUZZER   13
#define SERVO    14
#define ENC_B    20
#define ENC_A    18
#define ENC_S    19
#define BRAKE    25 //also BUILTIN_LED
#define TURN_L   2
#define TURN_R   3
#define IR_F     28
#define IR_I     27
#define IR_O     26
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
DisplayOurValues display;
Servo servo;
Encoder encoder;
int encoder_position = 0;
Motor left(LEFT_A, LEFT_B);
Motor right(RIGHT_A, RIGHT_B);
int servo_center = 90;
int turn_radius = 60;
unsigned long oldTime = 0;

volatile test_state state = test_state::LIGHTS;

void setup() {
  //initialize servo and motors
  if(!Serial) {
    Serial.begin(9600);
  }
  servo.attach(SERVO);
  servo.write(90);
  encoder.attach(ENC_A, ENC_B, Encoder::LatchMode::TWO03);
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
  pinMode(STOP,  INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  pinMode(IR_F,  INPUT);
  pinMode(IR_I,  INPUT);
  pinMode(IR_O,  INPUT);
  pinMode(IR_D,  INPUT);
  attachInterrupt(digitalPinToInterrupt(START), backISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(STOP), forwardISR, FALLING);
}

void backISR() {
  state = (test_state)(((((int)state - 1) % 10) + 10) % 10);
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
      if(millis() > oldTime + 1000) {
        oldTime = millis();
        digitalWrite(TURN_L, HIGH);
        digitalWrite(TURN_R, HIGH); 
      } else if(millis() > oldTime + 500) {
        digitalWrite(TURN_L, LOW);
        digitalWrite(TURN_R, LOW);
      }
      digitalWrite(BRAKE, HIGH);
      break;
    case test_state::DEBUG_LEDS:
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      digitalWrite(YELLOW, HIGH);
      break;
    case test_state::DEBUG_BUZZER:
        analogWrite(BUZZER, 0);
        delay(50);
        analogWriteFreq(440);
        analogWrite(BUZZER, 25);
        delay(450);
        analogWrite(BUZZER, 0);
        delay(50);
        analogWriteFreq(350);
        analogWrite(BUZZER, 25);
        delay(450);
      break;
    case test_state::ENCODER_SERVO:
      encoder_position = encoder.read();
      if (encoder_position > turn_radius) {
        encoder.write(turn_radius);
        encoder_position = turn_radius;
      } else if (encoder_position < -turn_radius) {
        encoder.write(-(turn_radius));
        encoder_position = -turn_radius;
      }
      servo.write(servo_center + encoder_position);
      if (digitalRead(ENC_S)) {
        digitalWrite(GREEN, HIGH);
        encoder.write(0);
      } else {
        digitalWrite(GREEN, LOW);
      }
      Serial.println("Encoder Position: " + String(encoder_position));
      break;
    case test_state::LEFT_MOTOR:
      left.forward(127);
      if(millis() > oldTime + 1000) {
        oldTime = millis();
        digitalWrite(TURN_L, HIGH);
      } else if(millis() > oldTime + 500) {
        digitalWrite(TURN_L, LOW);
      }
      break;
    case test_state::RIGHT_MOTOR:
      right.forward(127);
      if(millis() > oldTime + 1000) {
        oldTime = millis();        
        digitalWrite(TURN_R, HIGH);
        
      } else if(millis() > oldTime + 500) {        
        digitalWrite(TURN_R, LOW);
      }
      break;
    case test_state::FRONT_IR:
      if(millis() > oldTime + 50) {
        oldTime = millis();
        Serial.println("Front IR: " + String(analogRead(IR_F)));
      }
      break;
    case test_state::INSIDE_IR:
      if(millis() > oldTime + 50) {
        oldTime = millis();
        Serial.println("Inside IR: " + String(analogRead(IR_I)));
      }
      break;
    case test_state::OUTSIDE_IR:
      if(millis() > oldTime + 50) {
        oldTime = millis();
        Serial.println("Outside IR: " + String(analogRead(IR_O)));
      }
      break;
    case test_state::DOWN_IR:
      if(millis() > oldTime + 50) {
        oldTime = millis();
        Serial.println("Down IR: " + String(analogRead(IR_D)));
      }
      break;
    default:
      break;
  }
  if(curr_state != state) {
    resetAll();
  }
}

void resetAll() {
  servo.write(servo_center);
  left.brake();
  right.brake();
  digitalWrite(RED,    LOW);
  digitalWrite(GREEN,  LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(BUZZER, LOW);
  digitalWrite(BRAKE,  LOW);
  digitalWrite(TURN_L, LOW);
  digitalWrite(TURN_R, LOW);
  encoder.write(0);
}

void setup1() {
  while (millis() < 1000);
  display.setup();
  display.clear();
  display.displayValue("SafeTown 2023-2024", false);
  display.displayValue("SafeTown 2023-2024", true);
  display.displayValue("SafeTown 2023-2024", false);
  display.displayValue("SafeTown 2023-2024", true);
}

void loop1() {

}