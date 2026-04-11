#include <LiquidCrystal_I2C.h>
#include <gpsFreq.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

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

    lcd.clear();

    gpsFreq.formatFreq(strFreq);
    lcd.setCursor(2, 0);
    lcd.print(strFreq);

    gpsFreq.start(1);
}

