#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1X15.h>

Adafruit_SSD1306 display(128, 64, &Wire, 4);
Adafruit_ADS1115 ads;

#define BUFFSIZE 5
int index = 0;
double buff[BUFFSIZE] = {0};
double sum = 0;

const double T25 = 25 + 273.15;
const double RT0 = 10000.0;
const double beta = 3534.0;
const double Vcc = 5.0;
const double R = 5600.0;

double calcRt(double val)
{
    return R * ((Vcc / val) - 1);
}

double readTemp(double Rt)
{
    return (1 / ((1 / T25) + (1 / beta) * log(Rt / RT0)) - 273.15);
}

void setup() 
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay(); 
    
    ads.setGain(GAIN_ONE);
    ads.begin();

    uint16_t adc0 = ads.readADC_SingleEnded(0);
    double val = ads.computeVolts(adc0);
    
    for (int i = 0; i < BUFFSIZE; ++i)
    {
        buff[i] = val;
        sum += val;
    }
}

void loop() 
{
    uint16_t adc0 = ads.readADC_SingleEnded(0);
    double val = ads.computeVolts(adc0);
   
    sum -= buff[index];
    buff[index] = val;
    sum += val;
    index = (index+1) % BUFFSIZE;
    double result = sum / BUFFSIZE;
    
    double temp = readTemp(calcRt(val));

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    
    display.println(adc0);
    display.println(result, 4);
    display.println(temp, 2);
    
    display.display();
    
    delay(100);
}
