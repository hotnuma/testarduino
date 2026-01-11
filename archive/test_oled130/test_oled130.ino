#include <Adafruit_SH110X.h>

Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire /*, -1*/);

void setup()
{
    display.begin(0x3c, true);
    display.display();
}

void loop()
{
    display.clearDisplay();
    
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    
    display.setTextSize(2);
    
    //display.print("4 000 000 Hz");
    
    display.println("12345678901234567890");
    
    display.display();
    
    delay(500);
}
