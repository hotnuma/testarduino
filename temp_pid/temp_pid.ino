#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define BUFFSIZE 5
int index = 0;
int buff[BUFFSIZE] = {0};
int sum = 0;

const double T25 = 25 + 273.15;
const double RT25 = 10000.0;
const double R = 5600.0;
const double B = 3950.0;

const int PWM_PIN = 3;

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

    pinMode(PWM_PIN, OUTPUT);
}

void loop()
{
    int val = analogRead(A0);

    sum = sum - buff[index];
    buff[index] = val;
    sum = sum + val;
    index = (index+1) % BUFFSIZE;
    
    double temp = readTemp(sum / BUFFSIZE);

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("Te ");
    display.print(temp);
    display.println(" C");
    display.display();
    
    analogWrite(PWM_PIN, 140);
    
    delay(500);
}
