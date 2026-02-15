#include "Arduino.h"
#include "counter.h"
#include "shiftreg.h"
#include "math.h"

CounterIC counter;
ShiftRegIC shift;

void setup()
{
	counter.init(&shift, 10, 11, 12, 13);
    shift.init(1000, 14, 15, 16);

	Serial.begin(115200);
}

void loop()
{
}

