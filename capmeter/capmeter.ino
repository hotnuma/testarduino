#include <LiquidCrystal_I2C.h>
#include <gpsFreq.h>
#include <math.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

uint16_t nSample;
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

void loop()
{
    if (!gpsFreq.isBusy)
    {
        if (nSample > 0)
        {
            lcd.setCursor(2, 0);
            //gpsFreq.formatFreq(strFreq);
            lcd.print(gpsFreq.freq);
            
            lcd.setCursor(2, 1);
            double result = capa(R, gpsFreq.freq) - cal;
            //result *= 1e15;
            lcd.print(result);
        }
        
        ++nSample;
        
        gpsFreq.start(1);
    }
}
