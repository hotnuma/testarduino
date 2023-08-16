#include <LiquidCrystal_I2C.h>
#include <gpsFreq.h>
#include <math.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
#define LSIZE 16
#define LEMPTY "                "

const int CalPin = 7;
int allmodes = 12;

char tempstr[LSIZE+1];
char linestr[LSIZE+1];

void setup()
{
    pinMode(CalPin, INPUT_PULLUP);
    
    lcd.init();
    lcd.backlight();

    get_mode(allmodes);
}

int get_mode(int num)
{
    int adc = analogRead(A0);
    double q = ((double) adc / 1024.0 * (double) num);
    return (int) lround(q);    
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

double capa_711(double R, double freq)
{
    return (1 / (2 * log(2) * R * freq)) * 1e12;
}

double capa_555(double R1, double R2, double freq)
{
    return (1.44 / ( (R1 + (2 * R2)) * freq )) * 1e12;
}

bool first = true;

// Mode 1 : LM711 osc
double R_711 = 9990;
double cal_711 = 48;

// Mode 2 : 555 osc
double R1_555 = 9860;
double R2_555 = 9980;
double cal_555 = 200;

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
                cal_711 = capa_711(R_711, gpsFreq.freq);
                printval(linestr, "Cal...", 3);
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = capa_711(R_711, gpsFreq.freq) - cal_711;
                dtostrf(result, 1, 2, tempstr);
                printval(linestr, tempstr, 3);
                strcpy(linestr + (LSIZE-3), " pF");
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
        break;
        
        case 2:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                cal_555 = capa_555(R1_555, R2_555, gpsFreq.freq);
                printval(linestr, "Cal...", 3);
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = capa_555(R1_555, R2_555, gpsFreq.freq) - cal_555;
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

    gpsFreq.start(1);
}
