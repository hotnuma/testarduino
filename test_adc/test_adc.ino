#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        return;
    
    //display.display();
}

void loop()
{
    uint16_t Vi0 = analogRead(A0);
    double V = (Vi0 * 5.0) / 1024.0;
    
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    
    display.setTextSize(3);
    display.print(Vi0);
    display.println(" ADC");
    display.print(V);
    display.println(" V");
    
    display.display();
    
    delay(500);
}
