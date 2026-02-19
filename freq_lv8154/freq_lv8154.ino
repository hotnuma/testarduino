#include "Arduino.h"
#include "counter.h"
#include "shiftreg.h"
#include "math.h"

ShiftRegIC shift;

void setup()
{
	Serial.begin(9600);
	
    //                  gau gal gbu gbl
    counter.init(&shift, 12, 13, 10, 11);
    
    //             clk shld qh
    shift.init(1000, 4, 5, 3);
}

void loop()
{
    //Serial.println("test");
    
    if (counter.status == 1)
    {
        Serial.println("started");
        delay(500);
        return;
    }
    
    if (counter.status == 2)
    {
        Serial.println("stopped");
        
        // calc diff and display
        
        //~ uint32_t result = shift.readByte();
        //~ Serial.println(result);
    }
    
    counter.start(1);
    
    delay(500);
}

