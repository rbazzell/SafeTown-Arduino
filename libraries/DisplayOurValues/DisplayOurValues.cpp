  /*
  DisplayOurValues.cpp - Library for displaying system values.
  Created by Larissa Robinson, October 10, 2023.
  Released into the public domain.
*/

#include "Arduino.h"
#include "DisplayOurValues.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 adaSSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

//NOTE: Size 1 font seems to be 7 pixels tall

DisplayOurValues::DisplayOurValues()
{
}

void DisplayOurValues::showTestValues(int out_pin, int in_pin)
{
  adaSSD1306.clearDisplay();

  int out_read = analogRead(out_pin);
  int in_read = analogRead(in_pin);
  String out_heading = "Outer IR: ";
  String in_heading = "Inner IR: ";
  String out_display = out_heading + out_read;
  String in_display = in_heading + in_read;

  adaSSD1306.setTextSize(1);       
  adaSSD1306.setTextColor(SSD1306_WHITE);     
  adaSSD1306.setCursor(0,0);             
  adaSSD1306.println(out_display);
  adaSSD1306.println(in_display);

  adaSSD1306.display();
  delay(100);

}

void DisplayOurValues::setup(void) {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!adaSSD1306.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  adaSSD1306.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  adaSSD1306.clearDisplay();

  // Draw a single pixel in white
  adaSSD1306.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  adaSSD1306.display();
  delay(2000);
  // adaSSD1306.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // adaSSD1306.display(). These examples demonstrate both approaches...

  testdrawchar();

  testdrawstyles();

  // Invert and restore display, pausing in-between
  adaSSD1306.invertDisplay(true);
  delay(1000);
  adaSSD1306.invertDisplay(false);
  delay(1000);
}

void DisplayOurValues::testdrawchar(void) {
  adaSSD1306.clearDisplay();

  adaSSD1306.setTextSize(1);      // Normal 1:1 pixel scale
  adaSSD1306.setTextColor(SSD1306_WHITE); // Draw white text
  adaSSD1306.setCursor(0, 0);     // Start at top-left corner
  adaSSD1306.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') adaSSD1306.write(' ');
    else          adaSSD1306.write(i);
  }

  adaSSD1306.display();
  delay(2000);
}

void DisplayOurValues::testdrawstyles(void) {
  adaSSD1306.clearDisplay();

  adaSSD1306.setTextSize(1);             // Normal 1:1 pixel scale
  adaSSD1306.setTextColor(SSD1306_WHITE);        // Draw white text
  adaSSD1306.setCursor(0,0);             // Start at top-left corner
  adaSSD1306.println(F("Hello, world!"));

  adaSSD1306.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  adaSSD1306.println(3.141592);

  adaSSD1306.setTextSize(2);             // Draw 2X-scale text
  adaSSD1306.setTextColor(SSD1306_WHITE);
  adaSSD1306.print(F("0x")); 
  adaSSD1306.println(0xDEADBEEF, HEX);

  adaSSD1306.display();
  delay(2000);
}

void DisplayOurValues::displayValue(String input, bool invert) {

	if (invert) {
		adaSSD1306.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
	} else {
		adaSSD1306.setTextColor(SSD1306_WHITE);        // Draw white text
	};
	adaSSD1306.println(input);
	adaSSD1306.display();
}

void DisplayOurValues::displayIRValues() {
	adaSSD1306.print("Down IR: ");
	adaSSD1306.println(analogRead(down_ir_pin));
	adaSSD1306.print("Front IR: ");
	adaSSD1306.println(analogRead(front_ir_pin));
	adaSSD1306.print("Inner Left IR: ");
	adaSSD1306.println(analogRead(in_ir_pin));
	adaSSD1306.print("Outer Left IR: ");
	adaSSD1306.println(analogRead(out_ir_pin));
}

void DisplayOurValues::goToMenu() {
	menuTypes menu = getMenuType();
	int index = getMenuIndex();
	
	//This if statement is hardcoded (dislike)
	if (menu == MAIN) {
		//This switch statement is also essentially hardcoded (dislike)
		switch (index) {
			case 1:
				// Because of the way setMenuIndex() is written, setMenuType must always be called before setMenuIndex in cases like this
				setMenuType(NAV);
				break;
			case 2:
				setMenuType(SELDISPLAYVALUE);
				break;
			case 3:
				setMenuType(DISPLAYIR);
				break;
			default:
				break;
		};
		setMenuIndex(0);
	} else if (menu == NAV) {
		switch (index) {
			case 1:
				setMenuType(STARTPTLETS);
				setMenuIndex(1);
				break;
			case 2:
				setMenuType(ENDPTLETS);
				setMenuIndex(1);
				break;
			case 3:
				setMenuType(MAIN);
				setMenuIndex(0);
				break;
			default:
				setMenuIndex(0);
				break;
		};
		//NOT CORRECT YET
	} else if (menu == SELDISPLAYVALUE) {
		String temp;
		String temp2;
		switch (index) {
			case 0:
				setMenuItem(menu, 2, "0");
				setMenuIndex(index+1);
				break;
			case 1:
				setMenuType(DISPLAYVALUE);
				setMenuIndex(0);
				temp = getMenuItem(SELDISPLAYVALUE, 1);
				temp2 = getMenuItem(SELDISPLAYVALUE, 2);
				temp = temp + temp2;
				pinToDisplay = atoi((temp).c_str());
				break;
			default:
				setMenuItem(SELDISPLAYVALUE, 1, "0");
				setMenuType(MAIN);
				break;
		};
		//NOT CORRECT YET
	} else if (menu == DISPLAYVALUE) {
		setMenuItem(SELDISPLAYVALUE, 1, "0");
		setMenuItem(SELDISPLAYVALUE, 2, "");
		setMenuType(MAIN);
		setMenuIndex(0);
    } else if (menu == STARTPTLETS) {
		switch (index) {
			case 0:
				break;
			default:
				setMenuType(STARTPTNUMS);
				break;
		};
		setMenuIndex(1);
	} else if (menu == DISPLAYIR){
		setMenuType(MAIN);
		setMenuIndex(0);
    } else if (menu == STARTPTNUMS) {
		switch (index) {
			case 0:
				break;
			default:
				String row = getMenuItem(STARTPTLETS, 1);
				String col = getMenuItem(menu, 1);
				String select = "Selected: ";
				String startPt = select + row + col;
				setMenuItem(CONFIRMSELECTION, 1, startPt);
				setMenuType(CONFIRMSELECTION);	
				setMenuIndex(0);		
				break;
		};
    } else if (menu == ENDPTLETS) {
		switch (index) {
			case 0:
				 break;
			default:
				setMenuType(ENDPTNUMS);
				break;
		};
	    setMenuIndex(1);
    } else if (menu == ENDPTNUMS) {
		switch (index) {
			case 0:
				break;
			default:
				String row = getMenuItem(ENDPTLETS, 1);
				String col = getMenuItem(menu, 1);
				String select = "Selected: ";
				String endPt = select + row + col;
				setMenuItem(CONFIRMSELECTION, 1, endPt);
				setMenuType(CONFIRMSELECTION);
				setMenuIndex(0);				
				break;
		};
    } else { //CONFIRMSELECTION
		setMenuItem(STARTPTLETS, 1, "A");
		setMenuItem(STARTPTNUMS, 1, "1");
		setMenuItem(ENDPTLETS, 1, "A");
		setMenuItem(ENDPTNUMS, 1, "1");
		switch (index) {
			case 2:
				setMenuType(MAIN);
				setMenuIndex(0);
				break;
			case 3:
				setMenuType(STARTPTLETS);
				setMenuIndex(1);
				break;
			default:
				break;
		};
    };
}

DisplayOurValues::menuTypes DisplayOurValues::getMenuType() {
	return menuType;
}

void DisplayOurValues::setMenuType(menuTypes type) {
	menuType = type;
}

int DisplayOurValues::getMenuIndex() {
	menuTypes menu = getMenuType();
	//hardcoded
	if (menu == MAIN) {
		return mainIndex;
	} else if (menu == NAV) {
		return navIndex;
	} else if (menu == SELDISPLAYVALUE) {
		return displayValueIndex;
	} else if (menu == STARTPTLETS) {
		return startPtLetsIndex;
	} else if (menu == STARTPTNUMS) {
		return startPtNumsIndex;
	} else if (menu == ENDPTLETS) {
		return endPtLetsIndex;
	} else if (menu == ENDPTNUMS) {
		return endPtNumsIndex;
	} else {
		return confirmSelectionIndex;
	};
}

void DisplayOurValues::setMenuIndex(int index) {
	menuTypes menu = getMenuType();
	//hardcoded
	switch (menu) {
		case MAIN:
			//hardcoded
			if (index >= mainLength) {
				index = 0;
			} else if (index < 0) {
				index = mainLength-1;
			};
			mainIndex = index;
			break;
		case NAV:
			//hardcoded
			if (index >= navLength) {
				index = 0;
			} else if (index < 0) {
				index = navLength-1;
			};
			navIndex = index;
			break;
		//RENAME THE VARIABLE IN THE NEXT CASE
		case SELDISPLAYVALUE:
			//hardcoded
			if (index >= displayValueMenuLength) {
				index = 0;
			} else if (index < 0) {
				index = displayValueMenuLength-1;
			};
			displayValueIndex = index;
			break;
		case STARTPTLETS:
			if (index >= selPtLetsLength) {
				index = 0;
			} else if (index < 0) {
				index = selPtLetsLength-1;
			};
			startPtLetsIndex = index;
			break;
		case STARTPTNUMS:
			if (index >= selPtNumsLength) {
				index = 0;
			} else if (index < 0) {
				index = selPtNumsLength-1;
			};
			startPtNumsIndex = index;
			break;
		case ENDPTLETS:
			if (index >= selPtLetsLength) {
				index = 0;
			} else if (index < 0) {
				index = selPtLetsLength-1;
			};
			endPtLetsIndex = index;
			break;
		case ENDPTNUMS:
			if (index >= selPtNumsLength) {
				index = 0;
			} else if (index < 0) {
				index = selPtNumsLength-1;
			};
			endPtNumsIndex = index;
			break;
		default:
			if (index >= confirmSelectionLength) {
				index = 0;
			} else if (index < 0) {
				index = confirmSelectionLength-1;
			};
			confirmSelectionIndex = index;
			break;
	};
	
}

void DisplayOurValues::displayMenu() {
	if (updateScreen == true) {
		menuTypes menu = getMenuType();
		int length = getMenuLength();
		int index = getMenuIndex();
		int startPx;
		int startIndex = index >= numRowsOnScreen-1 ? index-1 : 0;
		int endIndex = index >= numRowsOnScreen ? startIndex + 1 : length-1;
	
		//hardcoded
		if (menu == MAIN) {
			startPx = 55;
		} else if (menu == NAV) {
			startPx = 40;
		} else if (menu == CONFIRMSELECTION) {
			startPx = 25;
		} else if (menu == DISPLAYIR) {
			startPx = 0;
		} else {
			startPx = 17;
		};
	
		adaSSD1306.clearDisplay();
		adaSSD1306.setTextSize(1);             
		adaSSD1306.setCursor(startPx,0);  
		
		if (menu != DISPLAYVALUE && menu != DISPLAYIR) {
			for (int i = 0; i < length; i++) {
				bool inPrintRange = i >= startIndex && i <= endIndex;
				if (i == index && menu != STARTPTLETS && menu != ENDPTLETS && menu != STARTPTNUMS && menu != ENDPTNUMS && menu != SELDISPLAYVALUE) {
					adaSSD1306.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
				} else {
					adaSSD1306.setTextColor(SSD1306_WHITE);
				};
				
				if (i == 0 || inPrintRange) {
			
					if (menu == SELDISPLAYVALUE && i >= 1) {
						adaSSD1306.print(getMenuItem(menu, i));
					} else {
						adaSSD1306.println(getMenuItem(menu, i));
					};
				};

			};
		} else if (menu == DISPLAYVALUE){
			int pinVal = analogRead(pinToDisplay);
			adaSSD1306.println(pinVal);
		} else {
			adaSSD1306.setTextColor(SSD1306_WHITE);
			displayIRValues();
		};
		
		adaSSD1306.display();
		updateScreen = false;
	};
}

String DisplayOurValues::getMenuItem(menuTypes menu, int index) {
	//hardcoded
	switch (menu) {
		case MAIN:
			return mainMenu[index];
		case NAV:
			return navMenu[index];
		case STARTPTLETS:
			return startPtLetters[index];
		case STARTPTNUMS:
			return startPtNums[index];
		case ENDPTLETS:
			return endPtLetters[index];
		case ENDPTNUMS:
			return endPtNums[index];
		case CONFIRMSELECTION:
			return confirmSelection[index];
		case SELDISPLAYVALUE:
			return displayValueMenu[index];
		default:
			return "";
	};
}

void DisplayOurValues::setMenuItem(menuTypes menu, int index, String val) {
	//hardcoded
	switch (menu) {
		case STARTPTLETS:
			startPtLetters[index] = val;
			break;
		case ENDPTLETS:
			endPtLetters[index] = val;
			break;
		case STARTPTNUMS:
			startPtNums[index] = val;
			break;
		case ENDPTNUMS:
			endPtNums[index] = val;
			break;
		case CONFIRMSELECTION:
			confirmSelection[index] = val;
			break;
		case SELDISPLAYVALUE:
			displayValueMenu[index] = val;
		default:
			break;
	};
}

int DisplayOurValues::getMenuLength() {
	menuTypes menu = getMenuType();
	//hardcoded
	switch (menu) {
		case MAIN:
			return mainLength;
		case NAV:
			return navLength;
		case STARTPTLETS:
		case ENDPTLETS:
			return selPtLetsLength;
		case STARTPTNUMS:
		case ENDPTNUMS:
			return selPtNumsLength;
		case CONFIRMSELECTION:
			return confirmSelectionLength;
		case SELDISPLAYVALUE:
			return displayValueMenuLength;
		default:
			return 1;
	};
}

void DisplayOurValues::setUpdateScreen(bool update) {
	updateScreen = update;
}

int DisplayOurValues::getNumRowsOrCols() {
	menuTypes menu = getMenuType();
	//hardcoded
	switch (menu) {
		case STARTPTLETS:
		case ENDPTLETS:
			return numRows;
		case STARTPTNUMS:
		case ENDPTNUMS:
			return numCols;
		case SELDISPLAYVALUE:
			return 10;
		default:
			return 0;
	};
}