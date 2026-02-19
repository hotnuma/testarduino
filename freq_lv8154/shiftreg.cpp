/*  shiftreg.cpp - Source file for SN54HC165 IC driver
    Copyright (c) 2020 Justin Holland.  All right reserved.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details. */

#include "Arduino.h"
#include "shiftreg.h"
#include "math.h"

void ShiftRegIC::init(uint32_t clk_freq,
                      uint8_t clk_pin,
                      uint8_t shld_pin,
                      uint8_t qh_pin,
                      bool complement)
{
    // clock output
    _CLK_pin = clk_pin;
    pinMode(_CLK_pin, OUTPUT);
    digitalWrite(_CLK_pin, LOW);
    timer_delay = (uint32_t) round((1.0 / clk_freq) * 1E6);
    _resetTimer = true;

    // shift/load output
    _SHLD_pin = shld_pin;
    //_shld = true;
    pinMode(_SHLD_pin, OUTPUT);
    digitalWrite(_SHLD_pin, HIGH);

    // serial input
    _QH_pin = qh_pin;
    pinMode(_QH_pin, INPUT);
}

uint32_t ShiftRegIC::readByte(bool load_switch)
{
    /* Read byte on SN54HC165 register
     * Arguement: True to load parallel data on IC prior to read
     *            False to read IC without loading data */
    
    uint32_t data_out = 0x00;

    if (load_switch)
        loadData();

    _shiftIn(&data_out);

    return data_out;
}

void ShiftRegIC::loadData()
{
    // Toggles SH/LD pin low on the SN54HC165

    digitalWrite(_SHLD_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(_SHLD_pin, HIGH);
    delayMicroseconds(2);
}

void ShiftRegIC::_shiftIn(uint32_t *data_out)
{
    // Reads serial data from the SN54HC165
    
    (*data_out) = 0x00;

    for (int i = 0; i < 8; ++i)
    {
        if (i == 0)
        {
            (*data_out) = digitalRead(_QH_pin);
        }
        else
        {
            _updateClock();
            (*data_out) = ((*data_out) << 1) | digitalRead(_QH_pin);
        }
    }

    _updateClock();
    digitalWrite(_CLK_pin, LOW);
}

void ShiftRegIC::_updateClock()
{
    // This function handles updates to the serial clock

    t0 = micros();
    tf = micros();

    while (tf - t0 <= timer_delay)
        tf = micros();
    
    digitalWrite(_CLK_pin, !digitalRead(_CLK_pin));

    t0 = micros();
    tf = micros();

    while (tf - t0 <= timer_delay)
        tf = micros();

    digitalWrite(_CLK_pin, !digitalRead(_CLK_pin));
}

