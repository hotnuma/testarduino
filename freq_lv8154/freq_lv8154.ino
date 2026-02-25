#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "counter.h"
#include "shiftreg.h"
#include "math.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
ShiftRegIC sreg;

void setup()
{
    lcd.init();
    lcd.backlight();
    
    //        freq clk shld qh
    sreg.init(1000, 9, 8, 7);

    //          shift gbu gbl gau gal
    counter.init(&sreg, 3, 4, 5, 6);
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

        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print(diff);
        
        counter.triggered = 0;
    }
}

