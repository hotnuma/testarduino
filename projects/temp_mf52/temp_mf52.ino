#include <Adafruit_SSD1306.h>

#define BUFFSIZE 5

Adafruit_SSD1306 display(128, 64, &Wire, -1);
uint16_t buff[BUFFSIZE] = {0};
int index = 0;
uint16_t sum = 0;

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

const double A = -1.572999722529719920233182151036999130e-03;
const double B = 6.587053134341457061307067988309427164e-04;
const double C = -1.464223058432023960280868313255098201e-06;

double calcTemp(double adc)
{
    double R1 = 10000;
    double R2 = R1 * (1023.0 / adc - 1.0);
    double logR2 = log(R2);
    double T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2));
    
    return T - 273.15;
}

double temp;

void loop()
{
    sum = sum - buff[index];
    buff[index] = analogRead(A0);
    sum = sum + buff[index];
    index = (index+1) % BUFFSIZE;

    temp = calcTemp((uint16_t) sum / BUFFSIZE);

    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    
    display.setCursor(5, 5);
    display.print("Te ");
    display.print(temp);
    display.println(" C");
    
    display.setCursor(64, 32);
    temp = (double) analogRead(A1) * 5.0 / 1024;
    display.print(temp);
    display.display();
    
    delay(500);
}

