#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"



class Encoder {
	public:
		enum class Direction {
			NOROTATION = 0,
			CLOCKWISE = 1,
			COUNTERCLOCKWISE = -1
		};
		
		enum class LatchMode {
			FOUR3 = 1,
			FOUR0 = 2,
			TWO03 = 3
		};
		
		// Constructor
		Encoder();
		void attach(int pinA, int pinB, LatchMode mode = LatchMode::TWO03);
		void detach();
		// functions
		long read();
		Direction direction();
		void write(long newPosition);
		void tick(void);
	
	private:

		int _pinA, _pinB;
		LatchMode _mode;
		volatile int8_t _oldState;
		
		volatile long _position;        // Internal position (4 times _positionExt)
		volatile long _positionExt;     // External position
		volatile long _positionExtPrev; // External position (used only for direction checking)

		unsigned long _positionExtTime;     // The time the last position change was detected.
		unsigned long _positionExtTimePrev; // The time the previous position change was detected.
		
};	
static Encoder* interruptArgument[32] = {nullptr};


static void _checkEncPos(Encoder* _enc_) {
	_enc_->tick();
}

static void _encISR0 () {
	_checkEncPos(interruptArgument[0]);
}
static void _encISR1 () {
	_checkEncPos(interruptArgument[1]);
}
static void _encISR2 () {
	_checkEncPos(interruptArgument[2]);
}
static void _encISR3 () {
	_checkEncPos(interruptArgument[3]);
}
static void _encISR4 () {
	_checkEncPos(interruptArgument[4]);
}
static void _encISR5 () {
	_checkEncPos(interruptArgument[5]);
}
static void _encISR6 () {
	_checkEncPos(interruptArgument[6]);
}
static void _encISR7 () {
	_checkEncPos(interruptArgument[7]);
}
static void _encISR8 () {
	_checkEncPos(interruptArgument[8]);
}
static void _encISR9 () {
	_checkEncPos(interruptArgument[9]);
}
static void _encISR10 () {
	_checkEncPos(interruptArgument[10]);
}
static void _encISR11 () {
	_checkEncPos(interruptArgument[11]);
}
static void _encISR12 () {
	_checkEncPos(interruptArgument[12]);
}
static void _encISR13 () {
	_checkEncPos(interruptArgument[13]);
}
static void _encISR14 () {
	_checkEncPos(interruptArgument[14]);
}
static void _encISR15 () {
	_checkEncPos(interruptArgument[15]);
}
static void _encISR16 () {
	_checkEncPos(interruptArgument[16]);
}
static void _encISR17 () {
	_checkEncPos(interruptArgument[17]);
}
static void _encISR18 () {
	_checkEncPos(interruptArgument[18]);
}
static void _encISR19 () {
	_checkEncPos(interruptArgument[19]);
}
static void _encISR20 () {
	_checkEncPos(interruptArgument[20]);
}
static void _encISR21 () {
	_checkEncPos(interruptArgument[21]);
}
static void _encISR22 () {
	_checkEncPos(interruptArgument[22]);
}
static void _encISR23 () {
	_checkEncPos(interruptArgument[23]);
}
static void _encISR24 () {
	_checkEncPos(interruptArgument[24]);
}
static void _encISR25 () {
	_checkEncPos(interruptArgument[25]);
}
static void _encISR26 () {
	_checkEncPos(interruptArgument[26]);
}
static void _encISR27 () {
	_checkEncPos(interruptArgument[27]);
}
static void _encISR28 () {
	_checkEncPos(interruptArgument[28]);
}
static void _encISR29 () {
	_checkEncPos(interruptArgument[29]);
}
static void _encISR30 () {
	_checkEncPos(interruptArgument[30]);
}
static void _encISR31 () {
	_checkEncPos(interruptArgument[31]);
}

static void attach_interrupt(int pin, Encoder* _enc_) {
			switch (pin) {
				case 0:
					//throw error if already attatched!!!
					interruptArgument[0] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR0, CHANGE);
					break;
				case 1:
					//throw error if already attatched!!!
					interruptArgument[1] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR1, CHANGE);
					break;
				case 2:
					//throw error if already attatched!!!
					interruptArgument[2] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR2, CHANGE);
					break;
				case 3:
					//throw error if already attatched!!!
					interruptArgument[3] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR3, CHANGE);
					break;
				case 4:
					//throw error if already attatched!!!
					interruptArgument[4] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR4, CHANGE);
					break;
				case 5:
					//throw error if already attatched!!!
					interruptArgument[5] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR5, CHANGE);
					break;
				case 6:
					//throw error if already attatched!!!
					interruptArgument[6] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR6, CHANGE);
					break;
				case 7:
					//throw error if already attatched!!!
					interruptArgument[7] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR7, CHANGE);
					break;
				case 8:
					//throw error if already attatched!!!
					interruptArgument[8] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR8, CHANGE);
					break;
				case 9:
					//throw error if already attatched!!!
					interruptArgument[9] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR9, CHANGE);
					break;
				case 10:
					//throw error if already attatched!!!
					interruptArgument[10] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR10, CHANGE);
					break;
				case 11:
					//throw error if already attatched!!!
					interruptArgument[11] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR11, CHANGE);
					break;
				case 12:
					//throw error if already attatched!!!
					interruptArgument[12] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR12, CHANGE);
					break;
				case 13:
					//throw error if already attatched!!!
					interruptArgument[13] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR13, CHANGE);
					break;
				case 14:
					//throw error if already attatched!!!
					interruptArgument[14] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR14, CHANGE);
					break;
				case 15:
					//throw error if already attatched!!!
					interruptArgument[15] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR15, CHANGE);
					break;
				case 16:
					//throw error if already attatched!!!
					interruptArgument[16] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR16, CHANGE);
					break;
				case 17:
					//throw error if already attatched!!!
					interruptArgument[17] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR17, CHANGE);
					break;
				case 18:
					//throw error if already attatched!!!
					interruptArgument[18] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR18, CHANGE);
					break;
				case 19:
					//throw error if already attatched!!!
					interruptArgument[19] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR19, CHANGE);
					break;
				case 20:
					//throw error if already attatched!!!
					interruptArgument[20] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR20, CHANGE);
					break;
				case 21:
					//throw error if already attatched!!!
					interruptArgument[21] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR21, CHANGE);
					break;
				case 22:
					//throw error if already attatched!!!
					interruptArgument[22] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR22, CHANGE);
					break;
				case 23:
					//throw error if already attatched!!!
					interruptArgument[23] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR23, CHANGE);
					break;
				case 24:
					//throw error if already attatched!!!
					interruptArgument[24] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR24, CHANGE);
					break;
				case 25:
					//throw error if already attatched!!!
					interruptArgument[25] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR25, CHANGE);
					break;
				case 26:
					//throw error if already attatched!!!
					interruptArgument[26] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR26, CHANGE);
					break;
				case 27:
					//throw error if already attatched!!!
					interruptArgument[27] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR27, CHANGE);
					break;
				case 28:
					//throw error if already attatched!!!
					interruptArgument[28] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR28, CHANGE);
					break;
				case 29:
					//throw error if already attatched!!!
					interruptArgument[29] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR29, CHANGE);
					break;
				case 30:
					//throw error if already attatched!!!
					interruptArgument[30] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR30, CHANGE);
					break;
				case 31:
					//throw error if already attatched!!!
					interruptArgument[31] = _enc_;
					attachInterrupt(digitalPinToInterrupt(pin), _encISR31, CHANGE);
					break;
				default:
					break;
			}	
		}
static void detach_interrupt(int pin) {
	if (pin >= 0 && pin < 32) {
		interruptArgument[pin] = nullptr;
		detachInterrupt(digitalPinToInterrupt(pin));
	}
}



#endif