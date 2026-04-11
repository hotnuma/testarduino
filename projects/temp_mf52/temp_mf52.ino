#include <Adafruit_SSD1306.h>
#define BUFFSIZE 5
#include "avgbuff.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);
avgbuff tempavg = {0};
avgbuff batavg = {0};

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();
    
    avgFill(&tempavg, analogRead(A0));
    avgFill(&batavg, analogRead(A1));
}

const float A = -1.572999722529719920233182151036999130e-03;
const float B = 6.587053134341457061307067988309427164e-04;
const float C = -1.464223058432023960280868313255098201e-06;

float readTemp()
{
    avgAdd(&tempavg, analogRead(A0));
    uint16_t adc = avgGet(&tempavg);
    
    float R1 = 10000;
    float R2 = R1 * (1023.0 / adc - 1.0);
    float logR2 = log(R2);
    float T = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2));
    
    return T - 273.15;
}

void loop()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    
    float temp = readTemp();
    display.setCursor(4, 4);
    display.print(temp, 1);
    display.println(" C");
    
    avgAdd(&batavg, analogRead(A1));
    int level = round((avgGet(&batavg) - 409) / 16);
    if (level < 0)
        level = 0;
    else if (level > 5)
        level = 5;
    display.setCursor(110, 32);
    display.print(level);
    
    display.display();
    
    delay(500);
}

