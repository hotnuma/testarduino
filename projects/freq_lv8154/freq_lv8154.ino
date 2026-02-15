#include "Arduino.h"
#include "counter.h"
#include "shiftreg.h"
#include "math.h"

CounterIC counter;
ShiftRegIC shift;

void setup()
{
	counter.init(&shift, 10, 11, 12, 13);

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

