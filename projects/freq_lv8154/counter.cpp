/*
    counter.cpp - Source file for SN74LV8154 IC driver
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

void CounterIC::set_serial_conn(ShiftRegIC *sreg)
{
	serial_output = sreg;
}

void CounterIC::init(uint8_t gau, uint8_t gal, uint8_t gbu, uint8_t gbl)
{
    GAU_pin = gau;
    GAL_pin = gal;
    GBU_pin = gbu;
    GBL_pin = gbl;

    pinMode(GAL_pin, OUTPUT);
    pinMode(GAU_pin, OUTPUT);
    pinMode(GBL_pin, OUTPUT);
    pinMode(GBU_pin, OUTPUT);
    digitalWrite(GAL_pin, HIGH);
    digitalWrite(GAU_pin, HIGH);
    digitalWrite(GBL_pin, HIGH);
    digitalWrite(GBU_pin, HIGH);
}

uint32_t CounterIC::readCounter32()
{
    uint32_t high_byte = readCounter(0);
    uint32_t low_byte = readCounter(1);
	
    uint32_t ret = (high_byte << 16) | low_byte;

	return ret;
}

uint32_t CounterIC::_readCounter(uint8_t cnum)
{
	uint32_t result = 0x00;

    //~ digitalWrite(RCLK_pin, HIGH);
    //~ delayMicroseconds(2);
    //~ digitalWrite(RCLK_pin, LOW);

	// read counter A
	if (cnum == 0)
		result = _readRegister(GAU_pin, GAL_pin);

	// read counter B
	else if (cnum == 1)
		result = _readRegister(GBU_pin, GBL_pin);

	return result;
}

uint32_t CounterIC::_readRegister(uint8_t up_pin, uint8_t low_pin)
{
    digitalWrite(up_pin, LOW);
    delayMicroseconds(2);

    uint32_t data_out = serial_output->readByte(true);

    digitalWrite(up_pin, HIGH);

    digitalWrite(low_pin, LOW);
    delayMicroseconds(2);

    data_out = (data_out << 8) | serial_output->readByte(true);

    digitalWrite(low_pin, HIGH);

    return data_out;
}

