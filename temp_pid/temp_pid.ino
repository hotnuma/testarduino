#include <Adafruit_SSD1306.h>
#include <PID_v1.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define BUFFSIZE 5
int index = 0;
int buff[BUFFSIZE] = {0};
int sum = 0;

const double T25 = 25 + 273.15;
const double RT25 = 10000.0;
const double R = 5600.0;
const double B = 3950.0;

#define PIN_PWM 3
double setpoint;
double input;
double output;
double Kp=7;
double Ki=0.1;
double Kd=0;

PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

double readTemp(int val)
{
    return (1 / ( (1 / T25) + (1 / B) * log( (R / RT25) * ((1024.0 / val) - 1))) - 273.15);
}

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();

    for (int i = 0; i < BUFFSIZE; ++i)
    {
        buff[i] = analogRead(A0);
        sum += buff[i];
        delay(100);
    }
    
    input = sum / BUFFSIZE;
    setpoint = 512;
    
    // turn the PID on
    myPID.SetMode(AUTOMATIC);
    
    pinMode(PIN_PWM, OUTPUT);
}

void loop()
{
    int val = analogRead(A0);

    sum = sum - buff[index];
    buff[index] = val;
    sum = sum + val;
    index = (index+1) % BUFFSIZE;
    
    int avg = sum / BUFFSIZE;
    double temp = readTemp(avg);

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    
    display.print("Te ");
    display.print(temp);
    display.println(" C");
    
    display.print("avg ");
    display.println(avg);

    input = avg;
    myPID.Compute();
    
    display.print("pwm ");
    display.println(output);
    
    //analogWrite(PIN_OUTPUT, Output);
    analogWrite(PIN_PWM, output);
    
    display.display();

    delay(100);
}
