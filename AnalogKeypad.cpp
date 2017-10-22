/*
  AnalogKeypad.cpp - Library for Arduino keypad in one analog pin.
  Created by Jakub Feret, 21.10. 2017.
*/

#include "Arduino.h"
#include "AnalogKeypad.h"

AnalogKeypad::AnalogKeypad(char keypadPin) {
	_keypadPin = keypadPin;
}

char AnalogKeypad::analogKeypressed() {	
	int value = analogRead(_keypadPin);	
	/*Serial.println(value);
  	delay(100);*/
	for (int i=0; i<16; i++) {
		current = millis();
		if ((value > 0) && (current - previous >= debounce)){ 			
			if (abs(value - analog[i]) < 5) {
				previous = current;
				return key[i];														  
			}		
		}		
		else {
			noKey = 'N';
			return noKey;
		}		
	}		
}


