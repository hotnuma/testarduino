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

class CounterIC;
class ShiftRegIC;
extern CounterIC counter;

class CounterIC
{
	public:
		
		CounterIC() {}

        void init(ShiftRegIC *sreg, uint8_t gbu, uint8_t gbl, uint8_t gau, uint8_t gal);
        void CounterIC::start(uint8_t period_secs = 1);
		uint32_t read();
        
        uint8_t y_pins[8] = {255};
        
        uint8_t period = 1;
        volatile uint8_t gate = 0;
        volatile uint8_t status = 0;

	private:
        
        uint32_t _readData();
        uint32_t _readRegister(uint8_t up_pin, uint8_t low_pin);
		uint8_t _GBU_pin = 255;
		uint8_t _GBL_pin = 255;
		uint8_t _GAU_pin = 255;
        uint8_t _GAL_pin = 255;
        
        ShiftRegIC *_shift = NULL;
};

#endif /* COUNTER_H_ */

