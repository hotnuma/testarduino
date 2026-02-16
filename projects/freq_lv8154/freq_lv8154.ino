#include "Arduino.h"
//#include "counter.h"
#include "shiftreg.h"
//#include "math.h"

//CounterIC counter;
ShiftRegIC shift;

void setup()
{
	//counter.init(&shift, 10, 11, 12, 13);
    
    //             clk shld qh
    shift.init(1000, 4, 3, 2);

	Serial.begin(115200);
}

void loop()
{
}

