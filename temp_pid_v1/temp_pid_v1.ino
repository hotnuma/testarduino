#include <Adafruit_SSD1306.h>
#include <PID_v1.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define BUFFSIZE 5
int index = 0;
int buff[BUFFSIZE] = {0};
int sum = 0;

const double T25 = 25 + 273.15;
const double RT0 = 10000.0;
const double R = 5600.0;
const double beta = 3950.0;

#define PIN_PWM 3

double setpoint;
double input;
double output;

double Kp=3;
double Ki=0.25;
double Kd=5;

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

double calcRt(int val)
{
    return R * ((1024.0 / val) - 1);
}

double readTemp(double Rt)
{
    return (1 / ((1 / T25) + (1 / beta) * log(Rt / RT0)) - 273.15);
}

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();

    input = analogRead(A0);
    
    setpoint = 512;
    
    // turn the PID on
    myPID.SetMode(AUTOMATIC);
    
    pinMode(PIN_PWM, OUTPUT);
}

void loop()
{
    input = analogRead(A0);
    myPID.Compute();
    analogWrite(PIN_PWM, output);
    
    double temp = readTemp(calcRt(input));

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

    delay(100);
}
