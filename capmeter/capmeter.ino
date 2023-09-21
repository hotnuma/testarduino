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

void printfreq()
{
    gpsFreq.formatFreq(tempstr);
    
    lcd_clear(linestr);
    lcd_cpy(linestr, tempstr, 3);
    strcpy(linestr + (STRSIZE-3), " Hz");
    
    lcd.setCursor(0, 0);
    lcd.print(linestr);
}


// Mode 1 : Low C 711 ---------------------------------------------------------

double low711_k = 1.44;
double low711_R = 1900;
double low711_C = 1126e-12;

double calc_low711(double k, double R, double freq)
{
    return (1 / (k * R * freq));
}


// Mode 2 : Low C 555 ---------------------------------------------------------

double high555_R1 = 1000;
double high555_R2 = 1000;
double high555_cal = 1e-6;

double calc_high555(double R1, double R2, double t)
{
    return t / (log(2) * (R1 + (2 * R2)));
}


//~ // Mode 3 : High C 711 ---------------------------------------------------------

double high711_k = 2 * log(2); //1.44;
double high711_R = 1900;
double high711_C = 1000e-9;

double calc_high711(double k, double R, double t)
{
    return t / (k * R);
}


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
                low711_C = calc_low711(low711_k, low711_R, gpsFreq.freq);
                
                lcd_clear(linestr);
                lcd_cpy(linestr, "Cal...", 3);
                
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = calc_low711(low711_k, low711_R, gpsFreq.freq) - low711_C;
                
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
                high555_cal = calc_high555(high555_R1, high555_R2, ((double) gpsFreq.freq / (double) 4e6));
                
                lcd_clear(linestr);
                lcd_cpy(linestr, "Cal...", 3);
                
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = calc_high555(high555_R1, high555_R2, ((double) gpsFreq.freq / (double) 4e6)) - high555_cal;
                
                dtostrf(result * 1e6, 1, 2, tempstr);
                
                lcd_clear(linestr);
                lcd_cpy(linestr, tempstr, 3);
                
                strcpy(linestr + (STRSIZE-3), " uF");
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            delay(1000);
        break;
        
        case 3:
            printfreq();
            
            if (digitalRead(CalPin) == LOW)
            {
                high711_C = calc_high711(high711_k, high711_R, ((double) gpsFreq.freq / (double) 4e6));
                
                lcd_clear(linestr);
                lcd_cpy(linestr, "Cal...", 3);
                
                lcd.setCursor(0, 1);
                lcd.print(linestr);
            }
            else
            {
                double result = calc_high711(high711_k, high711_R, ((double) gpsFreq.freq / (double) 4e6)) - high711_C;
                
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
