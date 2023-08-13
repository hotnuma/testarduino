#include <LiquidCrystal_I2C.h>
#include <gpsFreq.h>
#include <math.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

char strFreq[16];
double R = 10e3;
double fcal = 1498801;
double cal = 0;

double capa(double R, double freq)
{
    return (1 / (2 * log(2) * R * freq)) * 1e15;
}

void setup()
{
    lcd.init();
    lcd.backlight();

    cal = capa(R, fcal);
}

bool first = true;

void loop()
{
    if (!gpsFreq.isBusy)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            lcd.setCursor(2, 0);
            gpsFreq.formatFreq(strFreq);
            lcd.print(strFreq);
            lcd.print(" Hz");
            //lcd.print(gpsFreq.freq);
            
            lcd.setCursor(2, 1);
            double result = capa(R, gpsFreq.freq) - cal;
            lcd.print(result);
            lcd.print(" pF");
        }
        
        gpsFreq.start(1);
    }
}
