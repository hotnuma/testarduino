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

void CounterIC::init(ShiftRegIC *sreg, uint8_t gau, uint8_t gal, uint8_t gbu, uint8_t gbl)
{
	_serial_output = sreg;

    _GAU_pin = gau;
    _GAL_pin = gal;
    _GBU_pin = gbu;
    _GBL_pin = gbl;

    pinMode(_GAU_pin, OUTPUT);
    pinMode(_GAL_pin, OUTPUT);
    pinMode(_GBU_pin, OUTPUT);
    pinMode(_GBL_pin, OUTPUT);
    digitalWrite(_GAU_pin, HIGH);
    digitalWrite(_GAL_pin, HIGH);
    digitalWrite(_GBU_pin, HIGH);
    digitalWrite(_GBL_pin, HIGH);
}

void CounterIC::start(uint8_t period)
{
    status = 0;
    gatePeriod = period;
    gateInterrupts = 0;

    EICRA = _BV(ISC01);     // external interrupt on falling edge
    EIFR = _BV(INTF0);      // clear the interrupt flag (setting ISCnn can cause an interrupt)
    EIMSK = _BV(INT0);      // enable external interrupt
}

ISR(INT0_vect)
{
    // stop counting
    
    if (gpsFreq.gateInterrupts >= gpsFreq.gatePeriod)
    {
        EIMSK = 0;      // stop external interrupt
        ++gpsFreq.status;
        //digitalWrite(LED_BUILTIN, LOW);
    }
    
    // start counting
    else if (gpsFreq.gateInterrupts == 0)
    {   
        gpsFreq.status = 1;
        //digitalWrite(LED_BUILTIN, HIGH);
    }
    
    ++gpsFreq.gateInterrupts;
    ++gpsFreq.ppsTotal;
}

uint32_t CounterIC::readCounter32()
{
    uint32_t high_byte = _readRegister(_GAU_pin, _GAL_pin);
    uint32_t low_byte = _readRegister(_GBU_pin, _GBL_pin);

	return (high_byte << 16) | low_byte;
}

uint32_t CounterIC::_readRegister(uint8_t up_pin, uint8_t low_pin)
{
    digitalWrite(up_pin, LOW);
    delayMicroseconds(2);
    uint32_t data_out = _serial_output->readByte(true);
    digitalWrite(up_pin, HIGH);

    digitalWrite(low_pin, LOW);
    delayMicroseconds(2);
    data_out = (data_out << 8) | _serial_output->readByte(true);
    digitalWrite(low_pin, HIGH);

    return data_out;
}

