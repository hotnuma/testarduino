/*counter.h - Include file for SN74LV8154 IC driver
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

#ifndef COUNTER_H_
#define COUNTER_H_

#include "Arduino.h"

class ShiftRegIC;

class CounterIC
{
	public:
		
		CounterIC(ShiftRegIC *sreg) : serial_output(sreg)
		{
			GAL_pin = 255;
			GAU_pin = 255;
			GBL_pin = 255;
			GBU_pin = 255;
		}

        void init(uint8_t gau, uint8_t gal, uint8_t gbu, uint8_t gbl);
        void set_serial_conn(ShiftRegIC* s);

		uint32_t readCounter32();

        ShiftRegIC *serial_output;
        uint8_t GAL_pin;
		uint8_t GAU_pin;
		uint8_t GBL_pin;
		uint8_t GBU_pin;

	private:
        
		uint32_t _readCounter(uint8_t cnum);
        uint32_t _readRegister(uint8_t up_pin, uint8_t low_pin);
};

#endif /* COUNTER_H_ */

