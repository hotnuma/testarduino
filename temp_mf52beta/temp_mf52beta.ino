#include <Adafruit_SSD1306.h>

#define BUFFSIZE 5
int index = 0;
int buff[BUFFSIZE] = {0};
int sum = 0;

const double T25 = 25 + 273.15;
const double RT0 = 10000.0;
const double R = 5600.0;
const double beta = 3950.0;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

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

    int val = analogRead(A0);
    for (int i = 0; i < BUFFSIZE; ++i)
    {
        buff[i] = val;
        sum += val;
    }
}

void loop()
{
    int val = analogRead(A0);
    sum = sum - buff[index];
    buff[index] = val;
    sum = sum + val;
    index = (index+1) % BUFFSIZE;
    int result = sum / BUFFSIZE;
    
    double temp = readTemp(calcRt(result));

    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(5, 5);
    
    display.print("Te ");
    display.print(temp);
    display.println(" C");
    
    display.display();
    
    delay(500);
}
