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
		
		CounterIC() {}

        void init(ShiftRegIC *sreg, uint8_t gau, uint8_t gal, uint8_t gbu, uint8_t gbl);
		uint32_t readCounter32();

	private:
        
        uint32_t _readRegister(uint8_t up_pin, uint8_t low_pin);
        
        ShiftRegIC *_serial_output = NULL;
		uint8_t _GAU_pin = 255;
        uint8_t _GAL_pin = 255;
		uint8_t _GBU_pin = 255;
		uint8_t _GBL_pin = 255;
};

#endif /* COUNTER_H_ */

