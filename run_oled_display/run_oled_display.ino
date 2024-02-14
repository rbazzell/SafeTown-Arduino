#include "Arduino.h"
#include <String.h>
#include <DisplayOurValues.h>

int numClicks;
const int in_ir_pin = 27;
const int out_ir_pin = 28;
const int front_ir_pin = 26;
const int down_ir_pin = 29;
const int encoderClk = 16;
const int encoderDt = 17;
const int encoderSw = 3; //18;
//const int startPin = 3;
const int stopPin = 2;
int badValue = 0;
//const int reasonableTime = 14000;
//const int swReasonableTime = 330;
int itemIncrements = 0;
//int pastTime;
//int swPastTime;
enum turnStates {
	CW = 0,
	CCW = 1
};
int state = CW;
int count = 0;
DisplayOurValues disp = DisplayOurValues();

void setup() {
}

void loop() {
}

void setup1() {
  
  Serial.begin(115200);
  pinMode(in_ir_pin, INPUT);
  pinMode(out_ir_pin, INPUT);
  pinMode(front_ir_pin, INPUT);
  pinMode(down_ir_pin, INPUT);
  pinMode(encoderSw, INPUT);
  pinMode(encoderDt, INPUT);
  pinMode(encoderClk, INPUT);
 // pinMode(startPin, INPUT);
  pinMode(stopPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderSw), swInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(encoderClk), clkInterrupt, CHANGE);
 // attachInterrupt(digitalPinToInterrupt(startPin), startInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(stopPin), stopInterrupt, CHANGE);
  interrupts();
  disp.setup();

}

void loop1() {
  //This if statement is currently redundant, but if we put it here, this core would basically be idle (aside from interrupts) except for when it needs to rewrite the screen
  //Would have to write a getUpdateScreen function
  /**if (disp.getUpdateScreen() == true) {
    disp.displayMenu();
  };*/

  // if (count < 500 && count >= 0) {
  //   disp.displayValue("Hello, World!", false);
  // } else {
  //   disp.displayValue("It's a me, Mario!", true);
  //   if (count >= 1000) {
  //     count = 0;
  //   };
  // };
  // count++;

  // disp.setMenuType(DisplayOurValues::menuTypes::DISPLAYIR);
  // disp.setUpdateScreen(true);
  // disp.displayMenu();
	//disp.displayMenu();
}

void clkInterrupt() {
	int clkVal = digitalRead(encoderClk); //A
	int dtVal = digitalRead(encoderDt); //B
	int ind = disp.getMenuIndex();
  DisplayOurValues::menuTypes menu = disp.getMenuType();
	//int presentTime = micros();
	//int delta = presentTime-pastTime;

	// if (delta >= reasonableTime) {
		if (badValue >= 2) {
			state = !state;
		};
		
		if (state == CW){
			if (clkVal ^ dtVal) {
        switch (menu) {
          case DisplayOurValues::menuTypes::STARTPTLETS:
		      case DisplayOurValues::menuTypes::STARTPTNUMS:
		      case DisplayOurValues::menuTypes::ENDPTLETS:
		      case DisplayOurValues::menuTypes::ENDPTNUMS:
          case DisplayOurValues::menuTypes::SELDISPLAYVALUE:
            { 
              String currentItem = disp.getMenuItem(menu, ind+1);
              int limits = disp.getNumRowsOrCols();

              // For wraparound purposes
              String endItem;
              if (menu == DisplayOurValues::menuTypes::STARTPTLETS || menu == DisplayOurValues::menuTypes::ENDPTLETS) {
                endItem = "A";
              } else if (menu == DisplayOurValues::menuTypes::SELDISPLAYVALUE) {
                endItem = "0";
              } else {
                endItem = "1";
              };
              for (int i = 0; i < limits - 1; i++) {
	              endItem[0]++;
              };

              if (currentItem == endItem) {
                if (menu == DisplayOurValues::menuTypes::STARTPTLETS || menu == DisplayOurValues::menuTypes::ENDPTLETS) {
                  currentItem = "A";
                } else if (menu == DisplayOurValues::menuTypes::SELDISPLAYVALUE) {
                  currentItem = "0";
                } else {
                  currentItem = "1";
                };
                itemIncrements = 0;
              } else {
                currentItem[0]++;
                itemIncrements++;
              };
              disp.setMenuItem(menu, ind+1, currentItem);
            }
            break;
          case  DisplayOurValues::menuTypes::DISPLAYIR:
            Serial.println("in right place");
            Serial.println(analogRead(down_ir_pin));
            break;
          default:
            ind++;
            break;
        };
				badValue = 0;
				state = CW;
			} else {
				badValue++;
			};
		} else {
			if (clkVal ^! dtVal) {
        switch (menu) {
          case DisplayOurValues::menuTypes::STARTPTLETS:
		      case DisplayOurValues::menuTypes::STARTPTNUMS:
		      case DisplayOurValues::menuTypes::ENDPTLETS:
		      case DisplayOurValues::menuTypes::ENDPTNUMS:
          case DisplayOurValues::menuTypes::SELDISPLAYVALUE:
            { 
              String currentItem = disp.getMenuItem(menu, ind+1);
              int limits = disp.getNumRowsOrCols();
              if (currentItem == "A" || (currentItem == "1" && menu != DisplayOurValues::menuTypes::SELDISPLAYVALUE) || (currentItem == "0" && menu == DisplayOurValues::menuTypes::SELDISPLAYVALUE)) {
                for (int i = 0; i < limits - 1; i++) {
	                currentItem[0]++;
                };
                itemIncrements = 0;
              } else {
                currentItem[0]--;
                itemIncrements++;
              };
              disp.setMenuItem(menu, ind+1, currentItem);
            }
            break;
          case  DisplayOurValues::menuTypes::DISPLAYIR:
            Serial.println("in right place");
            Serial.println(analogRead(down_ir_pin));
            break;
          default:
            ind--;
            break;
        };
				badValue = 0;
				state = CCW;
			} else {
				badValue++;
			};
		};
	// }
	
	//pastTime = presentTime;
  disp.setMenuIndex(ind);
  disp.setUpdateScreen(true);
}

void swInterrupt() {
  int swVal = digitalRead(encoderSw);
  //int swPresentTime = millis();
	//int swDelta = swPresentTime-swPastTime;

  //if (swDelta >= 300) {
    if (swVal == 0) {
      disp.goToMenu();
    };
 // };
 
  //swPastTime = swPresentTime;
  disp.setUpdateScreen(true);
}

void startInterrupt() {
  int ind = disp.getMenuIndex();
  DisplayOurValues::menuTypes menu = disp.getMenuType();
  switch (menu) {
    case DisplayOurValues::menuTypes::SELDISPLAYVALUE:
      disp.setMenuItem(menu, ind++, "0");
      disp.setMenuIndex(ind++);
      break;
    default:
      break;
  }
}

void stopInterrupt() {
  disp.setMenuType(DisplayOurValues::menuTypes::MAIN);
  disp.setMenuIndex(0);
  disp.setUpdateScreen(true);
}
