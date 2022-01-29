#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        return;
}

void loop()
{
    const float T0 = 25 + 273.15;
    const float RT0 = 10000.0;
    const float R0 = 10000.0;
    const float B = 3435.0;

    float T = 0;
    
    uint16_t Vtn = analogRead(A0);
    T = 1 / ((1/T0) + (1/B)*log((R0/RT0)*((1024.0/Vtn) - 1))) - 273.15;

    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(5, 5);
    
    display.print("Te ");
    display.print(T);
    display.println(" C");
    
    display.display();
    
    delay(500);
}
