#include <Adafruit_SSD1306.h>
#include "ArduPID.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);
ArduPID myPID;

double input;
double output;
double setpoint = 512;

double Kp=2;
double Ki=1;
double Kd=1;

const int PIN_PWM = 3;

const double T25 = 25 + 273.15;
const double RT25 = 10000.0;
const double R = 5600.0;
const double B = 3950.0;

double readTemp(int val)
{
    return (1 / ( (1 / T25) + (1 / B) * log( (R / RT25) * ((1024.0 / val) - 1))) - 273.15);
}

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();

    pinMode(PIN_PWM, OUTPUT);

    input = analogRead(A0);
    
    myPID.begin(&input, &output, &setpoint, Kp, Ki, Kd);
    
    myPID.setOutputLimits(0, 255);
    myPID.setBias(255.0 / 2.0);
    myPID.setWindUpLimits(-20, 20);
    
    myPID.start();
}

void loop()
{
    input = analogRead(A0);
    myPID.compute();
    analogWrite(PIN_PWM, output);
    
    double temp = readTemp(input);

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    
    display.print("Te ");
    display.print(temp);
    display.println(" C");
    
    display.print("avg ");
    display.println(input);

    display.print("pwm ");
    display.println(output);
    
    display.display();

    //delay(100);
}
