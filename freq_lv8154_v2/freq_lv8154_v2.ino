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
    sreg.init(1000, 9, 8, 7);
    counter.init(&sreg, 3, 4, 5, 6);
}

uint32_t start = 0;
uint32_t now = 0;
uint8_t status = 0;

void loop()
{
    if (status == 2 && counter.status == 2)
    {
        status = 0;
        now = counter.read();
        uint32_t diff = now - start;

        lcd.clear();
        lcd.setCursor(0, 0);
        formatFreq(buffer, diff);
        lcd.print(buffer);
    }
    else if (status == 1 && counter.status == 1)
    {
        status = 2;
        start = counter.read();
    }
    else if (status == 0)
    {
        status = 1;
        counter.start(1);
    }
}

