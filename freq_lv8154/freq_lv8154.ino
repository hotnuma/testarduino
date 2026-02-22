#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "counter.h"
#include "math.h"

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup()
{
    lcd.init();
    lcd.backlight();

    //                 gbu gbl gau gal
    counter.init(NULL, A3, A2, A1, A0);
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

