#include <LiquidCrystal_I2C.h>
#include <gpsFreq.h>
#include <math.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

double R = 10e3;
double cal = 0;
const int CalPin = 7;

int nmodes = 12;
char strFreq[16];

void setup()
{
    double fcal = 1498801;
    
    pinMode(CalPin, INPUT_PULLUP);
    
    lcd.init();
    lcd.backlight();

    mode(nmodes);
    cal = capa(R, fcal);
}

int mode(int num)
{
    int adc = analogRead(A0);
    double q = ((double) adc / 1024.0 * (double) num);
    return (int) lround(q);    
}

void printfreq()
{
    lcd.setCursor(2, 0);
    gpsFreq.formatFreq(strFreq);
    lcd.print(strFreq);
    lcd.print(" Hz");
}

double capa(double R, double freq)
{
    return (1 / (2 * log(2) * R * freq)) * 1e15;
}

double capa555(double R1, double R2, double freq)
{
    return (1.44 / ((R1 + (2 * R2)) * freq)) * 1e12;
}

bool first = true;

void loop()
{
    if (gpsFreq.isBusy)
        return;

    if (first)
    {
        first = false;
        gpsFreq.start(1);
        return;
    }

    int fmode = mode(nmodes);
    
    switch (fmode)
    {
        case 0:
            printfreq();
        break;

        case 1:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                cal = capa(R, gpsFreq.freq);
                lcd.setCursor(0, 1);
                lcd.print("  Cal...        ");
            }
            else
            {
                lcd.setCursor(2, 1);
                double result = capa(R, gpsFreq.freq) - cal;
                lcd.print(result);
                lcd.print(" pF");
            }
        break;
        
        case 2:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                cal = capa555(R, R, gpsFreq.freq);
                lcd.setCursor(0, 1);
                lcd.print("  Cal...        ");
            }
            else
            {
                lcd.setCursor(2, 1);
                double result = capa555(R, R, gpsFreq.freq) /*- cal*/;
                lcd.print(result);
                lcd.print(" pF");
            }
        break;
        
        default:
            printfreq();
            
            lcd.setCursor(2, 1);
            lcd.print("Mode ");
            lcd.print(fmode);
        break;
    }

    gpsFreq.start(1);
}
