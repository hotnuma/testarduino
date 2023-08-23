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

double capa_LC(double L, double freq)
{
    return (1 / (pow((2 * M_PI * freq), 2) * L)) * 1e12;
}

bool first = true;

// Mode 1 : LM711 osc
double L_711 = 93.772*1e-6;
double cal_711 = 988;

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
                cal_711 = capa_LC(L_711, gpsFreq.freq);
                printval(linestr, "Cal...", 3);
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = capa_LC(L_711, gpsFreq.freq) - cal_711;
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
