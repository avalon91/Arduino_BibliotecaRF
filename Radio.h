#ifndef Radio_h
#define Radio_h

#include "Arduino.h"

class Radio{
	public:
		Radio(int canal, char role);
		void EnvieArray(int array[4]);
		void EnvieChars(char texto[10]);
		void RecebaArray();
		void RecebaChars();
};

#endif