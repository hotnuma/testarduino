#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
}

void loop()
{
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    
    display.setTextSize(2);
    display.println("12345678901234567890");
    
    display.display();
    
    delay(500);
}
