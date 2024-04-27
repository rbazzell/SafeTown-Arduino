#include <DisplayOurValues.h>

const int inside_ir = 27;  // Analog input pin that the potentiometer is attached to
const int outside_ir = 26;  // Analog output pin that the LED is attached to
const int front_ir = 28;
const int down_ir = 29;
bool go = false;

int insideValue, outsideValue;
DisplayOurValues disp = DisplayOurValues();

void setup() {
  // initialize serial communications at 9600 bps:
  //Serial.begin(9600);
  disp.setup();
}

void loop() {
  disp.showTestValues(outside_ir, inside_ir);
  // insideValue = analogRead(inside_ir);
  // outsideValue = analogRead(outside_ir);
  // // print the results to the Serial Monitor:
  // Serial.print("inside = ");
  // Serial.print(insideValue);
  // Serial.print("      outside = ");
  // Serial.println(outsideValue);
  // // wait 2 milliseconds before the next loop for the analog-to-digital
  // delay(100);
}
