#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int vref = 5.0;

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    //analogReference(EXTERNAL);
}

void loop()
{
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.setTextSize(2);
    
    int adc = analogRead(A0);
    
    display.println(adc);

    double val = (adc * vref) / 1024.0;
    
    display.print(val);
    display.println(" V");

    display.display();
    
    delay(500);
}
