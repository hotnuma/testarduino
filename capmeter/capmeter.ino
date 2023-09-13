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

double capa_RC(double R, double freq, double k)
{
    return (1 / (k * R * freq)) * 1e12;
}

//double capa_LC(double part, double freq)
//{
//    return (1 / (pow((2 * M_PI * freq), 2) * part));
//}

double LC_cal(double C2, double F2, double F1)
{
    double FF2 = pow(F2, 2);
    
    double result = C2 * (FF2 / (pow(F1, 2) - FF2));
    
    printf("C1 = %f\n", result * 1e12);
    
    return result;
}

double LC_capa(double F, double F1, double C1, double k)
{
    //return (1 / (pow(F1, 2) * part));
    
    return C1 * ((pow(F1, 2) / pow(F, 2)) - 1.0) * k;
}

bool first = true;

// Mode 1 : LM711 RC
double rc711_R = 1790;
double rc711_cal = 1231.305701;
double rc711_k = 1.412463;

// Mode 2 : LM711 LC
double C2 = 1000e-12;
double F1 = 523773;
double C1 = 1020e-12;
double k = 0.95;

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

        case 2:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                C1 = LC_cal(C2, gpsFreq.freq, F1);
                printval(linestr, "Cal...", 3);
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = LC_capa(gpsFreq.freq, F1, C1, k);
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
