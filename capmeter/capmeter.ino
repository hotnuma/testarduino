#include <LiquidCrystal_I2C.h>
#include <gpsFreq.h>
#include <math.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
#define LSIZE 16
#define LEMPTY "                "
char tempstr[LSIZE+1];
char linestr[LSIZE+1];

const int CalPin = 7;
int allmodes = 12;

int get_mode(int num)
{
    int adc = analogRead(A0);
    double q = ((double) adc / 1024.0 * (double) num);
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

double capa_LC(double L, double freq, double k)
{
    return (1 / (pow((2 * M_PI * freq), 2) * L)) * 1e12 * k;
}

double capa_RC(double R, double freq, double k)
{
    return (1 / (2 * log(2) * R * freq)) * 1e12 * k;
}

bool first = true;

// Mode 1 : LM711 LC
double lc711_L = 100e-6;
double lc711_cal = 1000;
double lc711_k = (10000.0/8957.0);

// Mode 3 : LM711 RC
double rc711_R = 10e3;
double rc711_cal = 1072; // 48
double rc711_k = (10000.0/9946.5);

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
            printfreq();
        break;

        case 1:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                lc711_cal = capa_LC(lc711_L, gpsFreq.freq, lc711_k);
                printval(linestr, "Cal...", 3);
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = capa_LC(lc711_L, gpsFreq.freq, lc711_k) - lc711_cal;
                dtostrf(result, 1, 2, tempstr);
                printval(linestr, tempstr, 3);
                strcpy(linestr + (LSIZE-3), " pF");
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
        break;
        
        case 3:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                rc711_cal = capa_RC(rc711_R, gpsFreq.freq, rc711_k);
                printval(linestr, "Cal...", 3);
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = capa_RC(rc711_R, gpsFreq.freq, rc711_k) - rc711_cal;
                dtostrf(result, 1, 2, tempstr);
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
