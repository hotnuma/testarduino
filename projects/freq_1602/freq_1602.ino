#include <LiquidCrystal_I2C.h>
#include <gpsFreq.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

uint16_t count;
char strFreq[16];

void setup()
{
    lcd.init();
    lcd.backlight();
}

void loop()
{
    if (gpsFreq.isBusy)
        return;

    if (count > 0)
    {
        lcd.clear();
        lcd.setCursor(2, 0);
        gpsFreq.formatFreq(strFreq);
        //lcd.print(gpsFreq.freq);
        //lcd.print(strFreq);
        lcd.printstr(strFreq);
    }
    
    ++count;
    
    gpsFreq.start(1);
}


