#include "Arduino.h"
#include "counter.h"
#include "shiftreg.h"
#include "math.h"

ShiftRegIC shift;

void setup()
{
	Serial.begin(9600);
	
    //                   gau gal gbu gbl
    counter.init(&shift, 12, 13, 10, 11);
    
    //             clk shld qh
    shift.init(1000, 4, 5, 3);
}

void loop()
{
    static uint32_t prev;
    static uint8_t started;
    
    if (counter.status == 1)
    {
        if (started == 0)
            prev = counter.readCounter32();
        started = 1;
    }
    else if (counter.status == 2)
    {
        Serial.println("stopped");
        uint32_t freq = counter.readCounter32() - prev;
        Serial.println(freq);
        counter.status = 0;
    }
    else
    {
        prev = 0;
        started = 0;
        counter.start(1);
    }

    delay(500);
}

