#pragma once
#include <Arduino.h>

class Defend {   // класс Defend
public:
	void setMCDefend(byte maxCurrentDefendPin, byte maxCurrentDefendOut);
	void setCCODefend(byte currentCutOffPin, byte currentCutOffOut);

	void setARPin(byte autoRepeatPin, byte autoRepeatOut);
	void setAutoReserve(byte autoReservePin, byte autoReserveOut);


	bool maxCurrentDefend(int stepTime);
	bool CurrentCutOff();

	void AutoRepeat(int stepTime,int numOfRepeat);
	void AutoReserve(byte permitPin);
	bool CommonSwitch(int pin, int out);

	void ClearOut();
private:
	byte _maxCurrentDefendPin;
	byte _currentCutOffPin;

	byte _maxCurrentDefendOut;
	byte _currentCutOffOut;

	byte _autoRepeatPin;
	byte _autoRepeatOut;

	byte _autoReservePin;
	byte _autoReserveOut;

	unsigned long _previousMillis;
	unsigned long _previousMillis1;

	byte _flag = 0;
	byte _flag1 = 0;
};




