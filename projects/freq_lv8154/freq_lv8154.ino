#include "Arduino.h"
#include "counter.h"
#include "shiftreg.h"
#include "math.h"

ShiftRegIC shift;
CounterIC counter(&shift);

void setup()
{
	counter.init(D10, D11, D12, D13);

	shift.CLK_pin = 40;
	shift.QH_pin = 22;
	shift.SHLD_pin = 38;
	
    shift.set_clock_freq(1000);
	shift.init();

	Serial.begin(115200);
}

void loop()
{
}

