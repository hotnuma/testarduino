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

uint8_t status = 0;

void loop()
{
    uint32_t prev = 0;
    
    if (counter.status == 1 && status != 1)
    {
        // Serial.println("started");
        prev = counter.readCounter32();
        status = 1;
    }
    else if (counter.status == 2)
    {
        Serial.println("stopped");
        uint32_t freq = counter.readCounter32() - prev;
        Serial.println(freq);
        status = 2;
        counter.start(1);
    }
    else
    {
        prev = 0;
        status = 0;
        counter.start(1);
    }

    delay(500);
}

