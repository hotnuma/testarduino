#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1X15.h>
#include "ArduPID.h"
#include <math.h>

Adafruit_SSD1306 display(128, 64, &Wire, 4);
Adafruit_ADS1115 ads;
ArduPID myPID;
#define PIN_PWM 3

double input;
double output;
double setpoint = 35;

double Kp=1;
double Ki=0;
double Kd=0;

#define BUFFSIZE 5
int index = 0;
double buff[BUFFSIZE] = {0};
double sum = 0;

const double T25 = 25 + 273.15;
const double RT0 = 10000.0;
const double beta = 3435.0;
const double Vcc = 3.93;
const double R = 5600.0;

unsigned long ptime;

double _calcRt(double val)
{
    return R * ((Vcc / val) - 1);
}

double readTemp()
{
    uint16_t adc0 = ads.readADC_SingleEnded(0);
    double val = ads.computeVolts(adc0);
    double Rt = _calcRt(val);
    return (1 / ((1 / T25) + (1 / beta) * log(Rt / RT0)) - 273.15);
}

double round_to(double val, double to)
{
    if (to == 0)
        return val;
    
    return round(val / to) * to;
}

void setup() 
{
    unsigned long ptime = millis();
    
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay(); 
    
    ads.setGain(GAIN_ONE);
    ads.begin();

    double temp = readTemp();
    
    for (int i = 0; i < BUFFSIZE; ++i)
    {
        buff[i] = temp;
        sum += temp;
    }

    pinMode(PIN_PWM, OUTPUT);
    
    setpoint = 35.0;
    
    myPID.begin(&input, &output, &setpoint, Kp, Ki, Kd);
    
    myPID.setOutputLimits(0, 255);
    myPID.setBias(255.0 / 2.0);
    myPID.setWindUpLimits(-20, 20);
    
    myPID.start();
}

void loop() 
{
    unsigned long now = millis();
    unsigned long elapsed = now - ptime;
    ptime = now;
    
    double temp = readTemp();
   
    sum -= buff[index];
    buff[index] = temp;
    sum += temp;
    index = (index+1) % BUFFSIZE;
    
    input = sum / BUFFSIZE;
    
    //output = 110;
    myPID.compute();
    analogWrite(PIN_PWM, output);
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0,0);
    
    display.println(input, 2);
    display.println(output, 2);
    
    //display.println(elapsed);
    
    display.display();
}
