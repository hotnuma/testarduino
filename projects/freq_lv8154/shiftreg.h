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


class ShiftRegIC {

	public:
		uint8_t SHLD_pin;
		uint8_t CLK_pin;
		uint8_t SER_pin;
		uint8_t QH_pin;
		uint8_t QHbar_pin;
		uint32_t clk_freq;

		ShiftRegIC()
		{
			SHLD_pin = 255;
			CLK_pin = 255;
			SER_pin = 255;
			QH_pin = 255;
			QHbar_pin = 255;
			clk_freq = 1000;
			_complement = false;
			_complement_set = false;
			_shld = false;
			_resetTimer = false;
			t0 = 0;
			tf = 0;
			timer_delay = 0;
		}

		//Pin setting functions
		void set_SHLD_pin(uint8_t p);
		void set_CLK_pin(uint8_t p);
		void set_SER_pin(uint8_t p);
		void set_QH_pin(uint8_t p);
		void set_QHbar_pin(uint8_t p);
		void set_clock_freq(uint32_t f);

		//Initialization function
		void init();

		//Serial clock update function
		void updateClock();

		//Shift register functions
		uint32_t readByte(bool load_switch);
		void loadData();

	private:
		bool _complement;
		bool _complement_set;
		bool _shld;
		bool _resetTimer;
		uint32_t t0;
		uint32_t tf;
		uint32_t timer_delay;
		void shiftIn(uint32_t* data_out);

};




#endif /* SHIFTREG_H_ */
