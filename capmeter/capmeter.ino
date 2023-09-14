#include <LiquidCrystal_I2C.h>
#include <gpsFreq.h>
#include <math.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
#define LSIZE 16
#define LEMPTY "                "
char tempstr[LSIZE+1];
char linestr[LSIZE+1];

#define ADC 1023
const int CalPin = 7;
int allmodes = 12;

int get_mode(int num)
{
    int adc = analogRead(A0);
    double q = ((double) adc / ADC * (double) num);
    return (int) lround(q);    
}

void get_frequency()
{
    if (gpsFreq.isBusy)
        return;

    gpsFreq.start(1);

    while (gpsFreq.isBusy == true) {}
}

void printfreq()
{
    lcd.setCursor(0, 0);
    gpsFreq.formatFreq(tempstr);
    
    printval(linestr, tempstr, 3);
    strcpy(linestr + (LSIZE-3), " Hz");
    lcd.print(linestr);
}

void printval(const char *outbuff, const char *str, int endchars)
{
    int len = strlen(str);
    int pos = (LSIZE - endchars) - len;
    strcpy(outbuff, LEMPTY);
    if (pos < 0)
        return;
    strncpy(outbuff+pos, str, len);
}

double RC_cal(double F1, double C2, double F2)
{
    return (C2 * (F2 / (F1 - F2)));
}

double RC_capa(double R, double freq, double k)
{
    return (1 / (k * R * freq)) /* * 1e12*/;
}

double RC_capa2(double F, double C1, double F1, double k)
{
    return C1 * ((F1 / F) - 1.0) * k;
}

bool first = true;

// Mode 1 : LM711 RC
double rc711_R = 1790;
double rc711_cal = 1231e-12;
double rc711_k = 1.45;

double rc711_C2 = 1000e-12;
double rc711_k2 = 1.0;

void setup()
{
    pinMode(CalPin, INPUT_PULLUP);
    
    lcd.init();
    lcd.backlight();

    get_mode(allmodes);
}

void loop()
{
    get_frequency();

    int mode = get_mode(allmodes);
    
    switch (mode)
    {
        case 0:
            //F1 = gpsFreq.freq;
            printfreq();
        break;

        case 1:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                rc711_cal = RC_capa(rc711_R, gpsFreq.freq, rc711_k);
                
                //rc711_cal = RC_cal(F1, rc711_C2, gpsFreq.freq);
                
                printval(linestr, "Cal...", 3);
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = RC_capa(rc711_R, gpsFreq.freq, rc711_k) - rc711_cal;
                
                //double result = RC_capa2(gpsFreq.freq, rc711_cal, F1, rc711_k2);
                
                dtostrf(result * 1e12, 1, 2, tempstr);
                printval(linestr, tempstr, 3);
                strcpy(linestr + (LSIZE-3), " pF");
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
        break;

        default:
            printfreq();
            
            lcd.setCursor(2, 1);
            lcd.print("Mode ");
            lcd.print(mode);
        break;
    }
}
