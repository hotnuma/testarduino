/*shiftreg.h - Include file for SN54HC165 IC driver
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

#ifndef SHIFTREG_H_
#define SHIFTREG_H_

#include "Arduino.h"


class ShiftRegIC
{
	public:
		
		ShiftRegIC()
		{
			_CLK_pin = 255;
			_SHLD_pin = 255;
			_QH_pin = 255;
			_complement = false;

			_shld = false;
			_resetTimer = false;
			t0 = 0;
			tf = 0;
			timer_delay = 0;
		}

		// initialization function
		void init(uint32_t clk_freq,
                  uint8_t clk_pin,
                  uint8_t shld_pin,
                  uint8_t qh_pin,
                  bool complement = false);

		// serial clock update function
		void updateClock();

		// shift register functions
		uint32_t readByte(bool load_switch);
		void loadData();

	private:
		
		void _shiftIn(uint32_t *data_out);
        
        uint8_t _SHLD_pin;
        uint8_t _CLK_pin;
        uint8_t _QH_pin;
        bool _complement;

		bool _shld;
		bool _resetTimer;
		
        uint32_t t0;
		uint32_t tf;
		uint32_t timer_delay;
};

#endif /* SHIFTREG_H_ */

