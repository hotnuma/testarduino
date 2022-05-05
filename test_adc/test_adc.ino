#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    analogReference(EXTERNAL);
}

void loop()
{
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.setTextSize(3);
    
    int val = analogRead(A0);
    
    display.println(val);

    float V = (val * 3.3) / 1023.0;
    
    display.println(V);

    display.display();
    
    delay(500);
}
