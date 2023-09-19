#include <LiquidCrystal_I2C.h>
#include <gpsFreq.h>
#include <math.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);
#define STREMPTY "                "
#define STRSIZE 16
char tempstr[STRSIZE+1];
char linestr[STRSIZE+1];

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
    gpsFreq.formatFreq(tempstr);
    
    lcd_clear(linestr);
    lcd_cpy(linestr, tempstr, 3);
    strcpy(linestr + (STRSIZE-3), " Hz");
    
    lcd.setCursor(0, 0);
    lcd.print(linestr);
}

void lcd_clear(const char *outbuff)
{
    strcpy(outbuff, STREMPTY);
}

void lcd_cpy(const char *outbuff, const char *str, int endchars)
{
    int len = strlen(str);
    int pos = (STRSIZE - endchars) - len;
    if (pos < 0)
        return;
    strncpy(outbuff+pos, str, len);
}

//void printval(const char *outbuff, const char *str, int endchars)
//{
//    int len = strlen(str);
//    int pos = (STRSIZE - endchars) - len;
//    strcpy(outbuff, STREMPTY);
//    if (pos < 0)
//        return;
//    strncpy(outbuff+pos, str, len);
//}

double RC_cal(double F1, double C2, double F2)
{
    return (C2 * (F2 / (F1 - F2)));
}

double RC_capa(double R, double freq, double k)
{
    return (1 / (k * R * freq));
}

double RC_capa2(double F, double C1, double F1, double k)
{
    return C1 * ((F1 / F) - 1.0) * k;
}

double calc_555HC(double R1, double R2, double t)
{
    return t / (log(2) * (R1 + (2 * R2)));
}

bool first = true;

// Mode 1 : LM711 RC
double rc711_R = 1800;
double rc711_cal = 1200e-12;
double rc711_k = 2 * log(2);

//double rc711_C2 = 1000e-12;
//double rc711_k2 = 1.0;

double h555_R1 = 1000;
double h555_R2 = 1000;
double h555_cal = 1e-6;

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
                
                lcd_clear(linestr);
                lcd_cpy(linestr, "Cal...", 3);
                
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = RC_capa(rc711_R, gpsFreq.freq, rc711_k) - rc711_cal;
                
                //double result = RC_capa2(gpsFreq.freq, rc711_cal, F1, rc711_k2);
                
                dtostrf(result * 1e12, 1, 2, tempstr);
                
                lcd_clear(linestr);
                lcd_cpy(linestr, tempstr, 3);
                strcpy(linestr + (STRSIZE-3), " pF");
                
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
        break;

        case 2:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                h555_cal = calc_555HC(h555_R1, h555_R2, ((double) gpsFreq.freq / (double) 4e6));
                
                lcd_clear(linestr);
                lcd_cpy(linestr, "Cal...", 3);
                
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = calc_555HC(h555_R1, h555_R2, ((double) gpsFreq.freq / (double) 4e6)) - h555_cal;
                
                dtostrf(result * 1e6, 1, 2, tempstr);
                
                lcd_clear(linestr);
                lcd_cpy(linestr, tempstr, 3);
                
                strcpy(linestr + (STRSIZE-3), " uF");
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            delay(1000);
        break;
        
        default:
            printfreq();
            
            lcd.setCursor(0, 1);
            lcd.print("Mode ");
            lcd.print(mode);
        break;
    }
}
