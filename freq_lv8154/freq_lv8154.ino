//#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "counter.h"
#include "math.h"

//LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup()
{
    //lcd.init();
    //lcd.backlight();
	
    Serial.begin(9600);
	
    //                   gau gal gbu gbl
    counter.init(NULL, A1, A0, A3, A2);
    counter.start();
}

void loop()
{
    static uint32_t last;
    static uint32_t now;
    static uint32_t diff;
    static uint32_t count = 0;

    if (counter.triggered == 1)
    {
        now = counter.read();
        diff = now - last;
        last = now;

        //~ lcd.clear();
        //~ lcd.setCursor(2, 0);
        //~ lcd.print(diff);
        
        Serial.println("--------------------------------------------");
        Serial.println(++count);
        //Serial.println(counter._readRegister(counter._GBU_pin, counter._GBL_pin));
        //Serial.println(counter._readRegister(counter._GAU_pin, counter._GAL_pin));
        Serial.println(diff);
        
        counter.triggered = 0;
    }
}

