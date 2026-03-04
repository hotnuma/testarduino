#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#include "counter.h"
#include "shiftreg.h"
#include "math.h"

#define BLANKLINE "                "
#define NCHARS 16
#define MAXCOUNT 500000000

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, NCHARS, 2);
ShiftRegIC sreg;
char _buffer[NCHARS + 1] = {0};

void printFreq(uint32_t freq)
{
    if (freq > MAXCOUNT)
        return;

    strcpy(_buffer, BLANKLINE);
    
    char temp[NCHARS + 1];
    ultoa(freq, temp, 10);
    uint8_t len = strlen(temp);
    if (len < 1 || len > 8)
        return;
    
    uint8_t pos = 13 - len - ((len - 1) / 3);
    char *dest = _buffer + pos;
    char *src = temp;
    
    for (uint8_t i = 0; i < len; ++i)
    {
        *dest++ = *src++;
        
        if (((len-1-i) % 3) == 0 && (i < len-1))
            *dest++ = ' ';
    }
    memcpy(_buffer + 13, "  C", 3);
    
    lcd.setCursor(0, 0);
    lcd.print(_buffer);
}

void setup()
{
    lcd.init();
    lcd.backlight();
    //pinMode(LED_BUILTIN, OUTPUT);
    sreg.init(1000, 9, 8, 7);
    counter.init(&sreg, 3, 4, 5, 6);
    counter.start();
}

uint32_t last = 0;
uint32_t now = 0;

void loop()
{
    if (counter.triggered == 1)
    {
        //digitalWrite(LED_BUILTIN, HIGH);
        now = counter.read();
        uint32_t diff = now - last;
        last = now;
        
        printFreq(diff);

        counter.triggered = 0;
        //digitalWrite(LED_BUILTIN, LOW);
    }
}

