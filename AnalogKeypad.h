/*
AnalogKeypad.h - Library for Arduino keypad in one analog pin.
Created by Jakub Feret, 21.10. 2017.
*/

#ifndef AnalogKeypad_h
#define AnalogKeypad_h

#include "Arduino.h"

class AnalogKeypad {
public:
	AnalogKeypad(char keypadPin);
	char analogKeypressed();	
private:
	char _keypadPin;
	int analog[17] = { 928, 910, 893, 876, 852, 837, 823, 808, 788, 775, 762, 750, 732, 721, 710, 699 };
	char key[17] = { '1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D' };
	unsigned long previous;
	unsigned long current;
	const long debounce = 250;
	char noKey = 'N';
};

#endif
