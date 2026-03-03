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

CounterIC counter;

void CounterIC::init(ShiftRegIC *sreg, uint8_t gbu, uint8_t gbl, uint8_t gau, uint8_t gal)
{
	_shift = sreg;

    _GBU_pin = gbu;
    _GBL_pin = gbl;
    _GAU_pin = gau;
    _GAL_pin = gal;
    pinMode(_GBU_pin, OUTPUT);
    pinMode(_GBL_pin, OUTPUT);
    pinMode(_GAU_pin, OUTPUT);
    pinMode(_GAL_pin, OUTPUT);
    digitalWrite(_GBU_pin, HIGH);
    digitalWrite(_GBL_pin, HIGH);
    digitalWrite(_GAU_pin, HIGH);
    digitalWrite(_GAL_pin, HIGH);
    
    if (_shift != NULL)
        return;

    for (uint8_t i = 0; i < 8; ++i)
    {
        if (y_pins[i] != 255)
            pinMode(y_pins[i], INPUT);
    }
}

void CounterIC::start(uint8_t period_secs)
{
    period = period_secs;
    gate = 0;
    status = 0;

    EICRA = _BV(ISC01); // external interrupt on falling edge
    EIFR = _BV(INTF0);  // clear the interrupt flag (setting ISCnn can cause an interrupt)
    EIMSK = _BV(INT0);  // enable external interrupt
}

ISR(INT0_vect)
{
    //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    // stop
    if (counter.gate >= counter.period)
    {
        EIMSK = 0;
        counter.status = 2;
        //digitalWrite(LED_BUILTIN, LOW);
    }
    
    // start
    else if (counter.gate == 0)
    {   
        counter.status = 1;
        //digitalWrite(LED_BUILTIN, HIGH);
    }
    
    ++counter.gate;
}

uint32_t CounterIC::read()
{
    uint32_t high_byte = _readRegister(_GBU_pin, _GBL_pin);
    uint32_t low_byte = _readRegister(_GAU_pin, _GAL_pin);

	return (high_byte << 16) | low_byte;
}

uint32_t CounterIC::_readRegister(uint8_t up_pin, uint8_t low_pin)
{
    uint32_t result = 0;
    
    digitalWrite(up_pin, LOW);
    delayMicroseconds(2);
    result = _readData();
    digitalWrite(up_pin, HIGH);

    digitalWrite(low_pin, LOW);
    delayMicroseconds(2);
    result = (result << 8) | _readData();
    digitalWrite(low_pin, HIGH);

    return result;
}

uint32_t CounterIC::_readData()
{
    if (_shift)
        return _shift->readByte();

    uint32_t result = 0x00;
    uint32_t val = 0x00;
    val = digitalRead(y_pins[7]);
    result = (result << 1) | val;
    val = digitalRead(y_pins[6]);
    result = (result << 1) | val;
    val = digitalRead(y_pins[5]);
    result = (result << 1) | val;
    val = digitalRead(y_pins[4]);
    result = (result << 1) | val;
    val = digitalRead(y_pins[3]);
    result = (result << 1) | val;
    val = digitalRead(y_pins[2]);
    result = (result << 1) | val;
    val = digitalRead(y_pins[1]);
    result = (result << 1) | val;
    val = digitalRead(y_pins[0]);
    result = (result << 1) | val;

	return result;
}

