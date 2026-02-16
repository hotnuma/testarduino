#include "Arduino.h"
//#include "counter.h"
//#include "shiftreg.h"
//#include "math.h"

//CounterIC counter;
//ShiftRegIC shift;

void setup()
{
	Serial.begin(9600);
	
    //counter.init(&shift, 10, 11, 12, 13);
    
    //             clk shld qh
    //shift.init(1000, 4, 3, 2);
}

void loop()
{
    Serial.println("test");
    
    //~ uint32_t result = shift.readByte();
    //~ Serial.println(result);
    
    delay(1000);
}

