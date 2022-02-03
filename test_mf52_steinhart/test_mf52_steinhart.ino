#include <Adafruit_SSD1306.h>

#define BUFFSIZE 5
int index = 0;
uint16_t buff[BUFFSIZE] = {0};
uint16_t sum = 0;
uint16_t value = 0;
uint16_t result = 0;

double A = 1.022420946287434274923899835130214342e-03;
double B = 2.531446513301488466726740789169980417e-04;
double C = 6.026532449323997115601352059075955167e-11;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

double calcTemp(double adc)
{
    double R1 = 10000;
    double R2 = R1 * (1023.0 / adc - 1.0);
    double logR2 = log(R2);
    double T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2));
    
    return T - 273.15;
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
}

void loop()
{
    // Remove the oldest entry from the sum
    sum = sum - buff[index];
    
    value = analogRead(A0);
    buff[index] = value;
    sum = sum + value;
    
    // Increment the index, and wrap to 0 if it exceeds the window size
    index = (index+1) % BUFFSIZE;
    
    result = sum / BUFFSIZE;
    
    double temp = calcTemp(result);

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
