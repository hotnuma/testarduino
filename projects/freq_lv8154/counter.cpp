/*counter.cpp - Source file for SN74LV8154 IC driver
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
#include "counter.h"
#include "shiftreg.h"
#include <math.h>

void CounterIC::set_gate_pins(uint8_t gau, uint8_t gal, uint8_t gbu, uint8_t gbl) {
/*Gate A and B pins on SN74LV8154
 *  GAL: Pin 3  [Gate A lower byte; active-low puts lower byte of stored counter A on Y bus]
 *  GAU: Pin 4  [Gate A upper byte; active-low puts upper byte of stored counter A on Y bus]
 *  GBL: Pin 5  [Gate B lower byte; active-low puts lower byte of stored counter B on Y bus]
 *  GBU: Pin 6  [Gate B upper byte; active-low puts upper byte of stored counter B on Y bus]
 */
	GAU_pin = gau;
	GAL_pin = gal;
	GBU_pin = gbu;
	GBL_pin = gbl;
}

void CounterIC::set_serial_conn(ShiftRegIC* s) {
/*Provide a pointer to a ShiftRegIC object that will allow data reads from
 *the SN74LV8154 to be performed via a single serial wire connection to the Arduino
 */
	serial_output = s;
}

void CounterIC::init() {
/*This function must be called just prior to entering the loop
 *
 */

	//Single 32-bit counter mode requires specific pin configuration
	if (strcmp(mode, "single") == 0) {
		_single = true;
		//Single counter mode requires CLKBEN to be connected to RCOA
		if (CLKBEN_pin != 255 || RCOA_pin != 255) {
			Serial.println("fatal error: From CounterIC::init() -- cannot define CLKBEN or RCOA pins for single counter mode.");
			while(1);
		}
	}
	else {
		_single = false;
	}

	//Initialize Gate pins
	if (GAL_pin == 255 || GAU_pin == 255 || GBL_pin == 255 || GBU_pin == 255) {
		Serial.println("fatal error: From CounterIC::init() -- all gate pins must be defined!");
		while(1);
	}
	else {
		pinMode(GAL_pin, OUTPUT);
		pinMode(GAU_pin, OUTPUT);
		pinMode(GBL_pin, OUTPUT);
		pinMode(GBU_pin, OUTPUT);
		digitalWrite(GAL_pin, HIGH);
		digitalWrite(GAU_pin, HIGH);
		digitalWrite(GBL_pin, HIGH);
		digitalWrite(GBU_pin, HIGH);
	}

	//Initialize Shift Register connection, if present
	if (serial_output != NULL) {
		_shift = true;
		if (Y0_pin != 255) {
			Serial.print("warning: From CounterIC::init() -- pins defined for parallel data output will not be used since shift register object has been specified.");
		}
	}
	else {
		_shift = false;
		if (Y0_pin == 255) {
			Serial.println("fatal error: From CounterIC::init() -- data pins (Y0-Y7) must be defined!");
			while(1);
		}
	}

	//Initialize CCLR pin
	if (CCLR_pin != 255) {
		_clear = true;
		pinMode(CCLR_pin, OUTPUT);
		digitalWrite(CCLR_pin, HIGH);
	}
	else {
		_clear = false;
	}

	//Initialize test pins
	if (a_trig_pin != 255) {
		_testA = true;
		pinMode(a_trig_pin, OUTPUT);
		digitalWrite(a_trig_pin, LOW);
		testA_delay = (uint32_t) round((1.0/a_freq)*1E6);
		_resetTimers = true;
	}
	else {
		_testA = false;
	}
	if (b_trig_pin != 255) {
		_testB = true;
		pinMode(b_trig_pin, OUTPUT);
		digitalWrite(b_trig_pin, LOW);
		testB_delay = (uint32_t) round((1.0/b_freq)*1E6);
		_resetTimers = true;
	}
	else {
		_testB = false;
	}
}

void CounterIC::update() {
/*This function must be called in the main loop if testing of Counters
 *A/B is being performed.  It can also be used to monitor for overflow condition
 *on Counter A.  Alternatively, overFlow() function can be called for this purpose
 */
	_updateRunning = true;
	tf_2 = micros();
	tf_3 = micros();


	//Handle timers for TestA and TestB signals
	if (_testA || _testB) {
		if (_resetTimers) {
			t0_2 = micros();
			t0_3 = micros();
			tf_2 = micros();
			tf_3 = micros();
			_resetTimers = false;
		}
	}

	if (_testA) {
		if (_resetTimer2) {
			t0_2 = micros();
			tf_2 = micros();
			_resetTimer2 = false;
		}

		if (tf_2 - t0_2 >= testA_delay/2) {
			digitalWrite(a_trig_pin, !digitalRead(a_trig_pin));
			_resetTimer2 = true;
		}
	}

	if (_testB) {
		if (_resetTimer3) {
			t0_3 = micros();
			tf_3 = micros();
			_resetTimer3 = false;
		}

		if (tf_3 - t0_3 >= testB_delay/2) {
			digitalWrite(b_trig_pin, !digitalRead(b_trig_pin));
			_resetTimer3 = true;
		}
	}

	//Handle Overflow status
	if (_overflow) {
		if (digitalRead(RCOA_pin) == LOW) {
			Serial.println("Counter A is full!");
		}
	}
}

uint32_t CounterIC::readCounter(uint8_t cnum)
{
	uint32_t data_out = 0x00;

    //~ digitalWrite(RCLK_pin, HIGH);
    //~ delayMicroseconds(2);
    //~ digitalWrite(RCLK_pin, LOW);

	// read A counter
	if (cnum = 0)
    {
		digitalWrite(GAU_pin, LOW);
		delayMicroseconds(2);
		
        if (_shift)
            data_out = serial_output->readByte(true);
		else
            data_out = readDataPins();
		
        digitalWrite(GAU_pin, HIGH);

		digitalWrite(GAL_pin, LOW);
		delayMicroseconds(2);
		
        if (_shift)
             data_out = (data_out << 8) | serial_output->readByte(true);
		else
             data_out = (data_out << 8) | readDataPins();
		
        digitalWrite(GAL_pin, HIGH);
	}

	// read B counter
	else if (cnum = 1)
    {
        digitalWrite(GBU_pin, LOW);
        delayMicroseconds(2);
        
        if (_shift)
            data_out = serial_output->readByte(true);
        else
            data_out = readDataPins();
        
        digitalWrite(GBU_pin, HIGH);

        digitalWrite(GBL_pin, LOW);
        delayMicroseconds(2);
        
        if (_shift)
            data_out = (data_out << 8) | serial_output->readByte(true);
        else
            data_out = (data_out << 8) | readDataPins();
        
        digitalWrite(GBL_pin, HIGH);
	}

	return data_out;
}

uint32_t CounterIC::readCounter_32bit()
{
/*Read the 32-bit value stored on the internal register of the SN74LV8154
 * This function can only be called when the IC is configured as a single 32-bit counter
 * by either connecting the CLKBEN pin to the RCOA pin or toggling Counter B on using this
 * library when an overflow occurs on Counter A.
 */
	uint32_t ret = 0xFFFF;

    uint32_t high_byte = readCounter("A");
    uint32_t low_byte = readCounter("B");
    ret = (high_byte << 16) | low_byte;

	return ret;
}

