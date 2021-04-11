#include "releydefend.h"

void Defend::setMCDefend(byte maxCurrentDefendPin, byte maxCurrentDefendOut){
	_maxCurrentDefendPin = maxCurrentDefendPin;
	_maxCurrentDefendOut = maxCurrentDefendOut;
	pinMode(_maxCurrentDefendPin, INPUT_PULLUP);
	pinMode(_maxCurrentDefendOut, OUTPUT);
}

void Defend::setCCODefend(byte currentCutOffPin, byte currentCutOffOut){
	_currentCutOffPin = currentCutOffPin;
	_currentCutOffOut = currentCutOffOut;
	pinMode(_currentCutOffPin, INPUT);
	pinMode(_currentCutOffOut, OUTPUT);
}

bool Defend::maxCurrentDefend(int stepTime){
	int workedFlag = 0;
	if(digitalRead(_maxCurrentDefendPin) == HIGH){
		if (_flag == 0){
		  _previousMillis = millis();
		  _flag = 1;
		}
		if (millis() - _previousMillis > stepTime){
			digitalWrite(_maxCurrentDefendOut, HIGH);
			Serial.println("maxCurrentDefend has worked");
			workedFlag++;
		}
	}
    if(digitalRead(_maxCurrentDefendPin) == LOW){
     _flag = 0;
    }
	if (workedFlag != 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Defend::CurrentCutOff(){
	int workedFlag = 0;
	if(digitalRead(_currentCutOffPin) == HIGH){
    digitalWrite(_currentCutOffOut, HIGH);
	Serial.println("CurrentCutOff has worked");
	workedFlag++;
    }
	if (workedFlag != 0) {
		return true;
	}
	else {
		return false;
	}
}

void Defend::setARPin(byte autoRepeatPin, byte autoRepeatOut) {
	_autoRepeatPin = autoRepeatPin;
	_autoRepeatOut = autoRepeatOut;
	pinMode(_autoRepeatPin, INPUT);
	pinMode(_autoRepeatOut, OUTPUT);
}

void Defend::setAutoReserve(byte autoReservePin, byte autoReserveOut) {
	_autoReservePin = autoReservePin;
	_autoReserveOut = autoReserveOut;
	pinMode(_autoReservePin, INPUT);
	pinMode(_autoReserveOut, OUTPUT);
}

void Defend::AutoRepeat(int stepTime, int numOfRepeat) {
	if (digitalRead(_autoRepeatPin) == HIGH) {
		if (_flag1 == 0) {
			_previousMillis1 = millis();
			_flag1++;
		}
	}
	digitalWrite(_autoRepeatOut, LOW);
	if (_flag1 <= numOfRepeat + 1 && millis() - _previousMillis1 >= stepTime && _flag1 != 0) {
		digitalWrite(_autoRepeatOut, HIGH);
		_previousMillis1 = millis();
		_flag1++;
		Serial.println("AutoRepeat has worked");
		Serial.println(_flag1 - 1);
	}
	if (_flag1 == numOfRepeat + 1) {
		_flag1 = 0;
	}
}



void Defend::AutoReserve(byte permitPin) {
	if (digitalRead(_autoReservePin) == HIGH && digitalRead(permitPin)==HIGH) {
		digitalWrite(_autoReserveOut, HIGH);
		Serial.println("AutoReserve has worked");
	}
}

bool Defend::CommonSwitch(int pin, int out) {
	pinMode(out, OUTPUT);
	if (pin > 0) {
		if (digitalRead(pin) == HIGH) {
			digitalWrite(out, HIGH);
			return true;
		}
	}
	else {
		if (digitalRead(pin*-1) == LOW) {
			digitalWrite(out, HIGH);
			return true;
		}
	}
	return false;
}

void Defend::ClearOut() {
	digitalWrite(_maxCurrentDefendOut, LOW);
	digitalWrite(_currentCutOffOut, LOW);
	digitalWrite(_autoRepeatOut, LOW);
	digitalWrite(_autoReserveOut, LOW);
}
