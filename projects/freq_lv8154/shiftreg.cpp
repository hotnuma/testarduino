/*shiftreg.cpp - Source file for SN54HC165 IC driver
  Copyright (c) 2020 Justin Holland.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
 */

#include "Arduino.h"
#include "shiftreg.h"
#include "math.h"

void ShiftRegIC::set_SHLD_pin(uint8_t p) {
/*Shift or Load innput pin on SN54HC165
 * SH/LD: Pin 1  [When High Data is shifted; when low data is loaded from parallel inputs]
 */
	SHLD_pin = p;
}

void ShiftRegIC::set_CLK_pin(uint8_t p) {
/*Clock input pin on SN54HC165
 * CLK: Pin 2
 */
	CLK_pin = p;
}

void ShiftRegIC::set_QH_pin(uint8_t p) {
/*Serial output pin on SN54HC165
 * QH: Pin 9
 */
	QH_pin = p;
}

void ShiftRegIC::set_QHbar_pin(uint8_t p) {
/*Complementary serial output pin on SN54HC165
 * QH_bar: Pin 7
 */
	QHbar_pin = p;
}

void ShiftRegIC::set_SER_pin(uint8_t p) {
/*Serial input pin on SN54HC165
 * SER: Pin 10
 *
 * NOTE: This IC does not permit bidirectional comms.  The serial input can
 * only be used for daisy-chaining multiple SN54HC165 ICs together.
 */
	SER_pin = p;
}

void ShiftRegIC::set_clock_freq(uint32_t f) {
/*Set frequency in Hz for clocking serial data out of the SN54HC165
 *
 */
	clk_freq = f;
}

void ShiftRegIC::init() {
/*This function must be called just prior to entering the loop
 *
 */
	//Initalize SH/LD Pin
	if (SHLD_pin != 255) {
		_shld = true;
		pinMode(SHLD_pin, OUTPUT);
		digitalWrite(SHLD_pin, HIGH);
	}
	else {
		_shld = false;
		Serial.println("warning: From ShiftRegIC::init() -- you have not defined SH/LD pin. Make sure you have an external source for it.");
	}

	//Initialize clock
	if (CLK_pin != 255) {
		pinMode(CLK_pin, OUTPUT);
		digitalWrite(CLK_pin, LOW);
		timer_delay = (uint32_t) round((1.0/clk_freq)*1E6);
		_resetTimer = true;
	}
	else {
		Serial.println("fatal error: From ShiftRegIC::init() -- CLK_pin must be defined.");
		while(1);
	}

	//Initialize serial input pin(s)
	if (QH_pin == 255 && QHbar_pin == 255) {
		Serial.println("fatal error:  From ShiftRegIC::init() --  data output pin(s) for the shift register must be defined (QH or QHbar)");
		while(1);
	}
	else if (QH_pin == 255 && QHbar_pin != 255) {
		_complement = true;
		pinMode(QHbar_pin, INPUT);
	}
	else if (QH_pin != 255 && QHbar_pin == 255) {
		_complement = false;
		pinMode(QH_pin, INPUT);
	}
	else if (QH_pin != 255 && QHbar_pin != 255) {
		if (!_complement_set) {
			_complement = false;
			pinMode(QH_pin, INPUT);
			Serial.println("warning: From ShiftRegIC::init() -- QH and complement pins defined but preference not set...using QH as default");
		}
		else {
			if (_complement) {
				pinMode(QHbar_pin, INPUT);
			}
			else {
				pinMode(QH_pin, INPUT);
			}
		}
	}
}

void ShiftRegIC::updateClock() {
/*This function handles updates to the serial clock
 *
 */

	t0 = micros();
	tf = micros();

	while (tf-t0 <= timer_delay) {
		tf = micros();
	}
	digitalWrite(CLK_pin, !digitalRead(CLK_pin));

	t0 = micros();
	tf = micros();

	while (tf-t0 <= timer_delay) {
		tf = micros();
	}
	digitalWrite(CLK_pin, !digitalRead(CLK_pin));

}

uint32_t ShiftRegIC::readByte(bool load_switch) {
/*Read byte on SN54HC165 register
 * Arguement: True to load parallel data on IC prior to read
 *            False to read IC without loading data
 */
	uint32_t data_out = 0x00;

	if (_shld && load_switch) {
		loadData();
		shiftIn(&data_out);
	}
	else if (_shld && !load_switch) {
		shiftIn(&data_out);
	}
	else if (!_shld) {
		Serial.println("warning:  From ShiftRegIC::readByte() -- Load switch argument ignored because SHLD_pin is undefined.");
		shiftIn(&data_out);
	}

	return data_out;
}

void ShiftRegIC::loadData() {
/*Toggles SH/LD pin low on the SN54HC165
 *
 */
	if (_shld) {
		digitalWrite(SHLD_pin, LOW);
		delayMicroseconds(2);
		digitalWrite(SHLD_pin, HIGH);
		delayMicroseconds(2);
	}
	else {
		Serial.println("warning:  From ShiftRegIC::loadData() -- Cannot load data because SHLD_pin is undefined.");
	}
}

void ShiftRegIC::shiftIn(uint32_t* data_out) {
/*Reads serial data from the SN54HC165
 *
 */
	(*data_out) = 0x00;

	if (_complement) {
		for (int i=0;i<8;i++) {
			if (i == 0) {
				(*data_out) = digitalRead(QHbar_pin);
			}
			else {
				updateClock();
				(*data_out) = ((*data_out) << 1) | digitalRead(QHbar_pin);
			}
		}
	}
	else {
		for (int i=0; i<8;i++) {
			if (i == 0) {
				(*data_out) = digitalRead(QH_pin);
			}
			else {
				updateClock();
				(*data_out) = ((*data_out) << 1) | digitalRead(QH_pin);
			}
		}
	}
	updateClock();
	digitalWrite(CLK_pin, LOW);
}


