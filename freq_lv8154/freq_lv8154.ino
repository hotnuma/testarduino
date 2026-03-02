#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "counter.h"
#include "shiftreg.h"
#include "math.h"

#define NCHARS 16

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, NCHARS, 2);
ShiftRegIC sreg;
char buffer[NCHARS + 1] = {0};

void formatFreq(char *result, uint32_t freq)
{
    char temp[NCHARS + 1];

    ltoa(freq, temp, 10);
    char *pf = temp;
    uint8_t len = strlen(temp);
    
    for (uint8_t i = 0; i < len; ++i)
    {
        *result++ = *pf++;
        
        if ((len - i - 1) % 3 == 0 && i < len-1)
            *result++ = ' ';
    }

    *result++ = 0;
}

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
        lcd.setCursor(0, 0);
        //strcpy(buffer, "                ");
        
        formatFreq(buffer, diff);
        lcd.print(buffer);
        
        counter.triggered = 0;
    }
}

