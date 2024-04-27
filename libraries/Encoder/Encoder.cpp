#include "Encoder.h"
#include "Arduino.h"

#define LATCH0 0
#define LATCH3 3


const int8_t KNOBDIR[] = {
    0, -1, 1, 0,
    1, 0, 0, -1,
    -1, 0, 0, 1,
    0, 1, -1, 0
	};


Encoder::Encoder() {
	_position = 0;
	_positionExt = 0;
	_positionExtPrev = 0;
}

void Encoder::attach(int pinA, int pinB, Encoder::LatchMode mode) {
	_pinA = pinA;
	_pinB = pinB;
	_mode = mode;
	
	pinMode(_pinA, INPUT_PULLUP);
	pinMode(_pinB, INPUT_PULLUP);
	
	attach_interrupt(_pinA, this);
	attach_interrupt(_pinB, this);
	
	int sig1 = digitalRead(_pinA);
	int sig2 = digitalRead(_pinB);
	_oldState = sig1 | (sig2 << 1);
}

void Encoder::detach() {
	detach_interrupt(_pinA);
	detach_interrupt(_pinB);
}

long Encoder::read() {
	return _positionExt;
}

Encoder::Direction Encoder::direction() {
	Encoder::Direction ret = Direction::NOROTATION;
	
	if (_positionExtPrev > _positionExt) {
		ret = Direction::COUNTERCLOCKWISE;
		_positionExtPrev = _positionExt;
	} else if (_positionExtPrev < _positionExt) {
		ret = Direction::CLOCKWISE;
		_positionExtPrev = _positionExt;
	} else {
		ret = Direction::NOROTATION;
		_positionExtPrev = _positionExt;
	}

	return ret;
}

void Encoder::write(long newPosition) {
	switch (_mode) {
		case LatchMode::FOUR3:
		case LatchMode::FOUR0:
			_position = ((newPosition << 2) | (_position & 0x03L));
			_positionExt = newPosition;
			_positionExtPrev = newPosition;
			break;
		case LatchMode::TWO03:
			_position = ((newPosition << 1) | (_position & 0x01L));
			_positionExt = newPosition;
			_positionExtPrev = newPosition;
			break;
  }
}

void Encoder::tick(void) {
	int sig1 = digitalRead(_pinA);
	int sig2 = digitalRead(_pinB);
	int8_t thisState = sig1 | (sig2 << 1);
	
	if (_oldState != thisState) {
		_position += KNOBDIR[thisState | (_oldState << 2)];
		_oldState = thisState;

		switch (_mode) {
		case LatchMode::FOUR3:
			if (thisState == LATCH3) {
				_positionExt = _position >> 2;
				_positionExtTimePrev = _positionExtTime;
				_positionExtTime = millis();
			}
			break;

		case LatchMode::FOUR0:
			if (thisState == LATCH0) {
				_positionExt = _position >> 2;
				_positionExtTimePrev = _positionExtTime;
				_positionExtTime = millis();
			}
			break;

		case LatchMode::TWO03:
			if ((thisState == LATCH0) || (thisState == LATCH3)) {
				_positionExt = _position >> 1;
				_positionExtTimePrev = _positionExtTime;
				_positionExtTime = millis();
			}
			break;
		}
	}
}

