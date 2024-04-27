#ifndef DisplayOurValues_h
#define DisplayOurValues_h

#include "Arduino.h"
#include "DisplayOurValues.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <String.h>

class DisplayOurValues {
  public:
	enum menuTypes {
		MAIN,
		NAV,
		SELDISPLAYVALUE,
		DISPLAYVALUE,
		STARTPTLETS,
		STARTPTNUMS,
		ENDPTLETS,
		ENDPTNUMS,
		CONFIRMSELECTION,
		DISPLAYIR
	};
  
    DisplayOurValues();
	void setup();
    void showTestValues(int out_pin = 28, int in_pin = 27);
	void displayIRValues();
	void displayValue(String input, bool invert);
	void displayMenu();
	void goToMenu();
	void clear();

	void setMenuIndex(int index);
	void setMenuType(menuTypes type);
	void setUpdateScreen(bool update);	
	void setMenuItem(menuTypes menu, int index, String val);

	int getMenuIndex();
	menuTypes getMenuType();
	String getMenuItem(menuTypes menu, int index);
	int getMenuLength();
	int getNumRowsOrCols();
	
  private:
	//WILL NEED TO CHANGE BASED ON WHAT YOU PUT IN THE MENUS
	static const int numRowsOnScreen = 4;
	static const int mainLength = 4;
	static const int navLength = 4;
	static const int selPtLetsLength = 2;
	static const int selPtNumsLength = 2;
	static const int confirmSelectionLength = 4;
	static const int displayValueMenuLength = 3;
	
	int pinToDisplay;
	
	int mainIndex;
	int navIndex;
	int startPtLetsIndex;
	int startPtNumsIndex;
	int endPtLetsIndex;
	int endPtNumsIndex;
	int confirmSelectionIndex;
	int displayValueIndex;
	bool updateScreen = false;
	menuTypes menuType = MAIN;
	
	//THESE WILL HAVE TO EVENTUALLY BE CHANGED TO PULL FROM MEMORY INSTEAD
	int numRows = 3;
	int numCols = 4;
	
	String mainMenu[mainLength] = {"MENU:", "1. End/Start Select", "2. Display Pin Value", "3. Display IR Values"};
	String navMenu[navLength] = {"NAV MENU:", "1. Select Start Point", "2. Select End Point", "3. Back"};
	String startPtLetters[selPtLetsLength] = {"Select Start Row:", "A"};
	String startPtNums[selPtNumsLength] = {"Select Start Col:", "1"};
	String endPtLetters[selPtLetsLength] = {"Select End Row:", "A"};
	String endPtNums[selPtNumsLength] = {"Select End Col:", "1"};
	String confirmSelection[confirmSelectionLength] = {"Confirm Point:", "Selected:", "1. Confirm", "2. Change"};
	String displayValueMenu[displayValueMenuLength] = {"Select GPIO Pin:", "0", ""};
	//be able to read out the value on an ADC as well

};

#endif