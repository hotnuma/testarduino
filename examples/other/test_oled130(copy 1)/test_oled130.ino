#include <oled.h>

OLED display(A4, A5, 16, OLED::W_128, OLED::H_64, OLED::CTRL_SH1106, 0x3C);

void setup()
{
    display.begin();
}

void loop()
{
    display.clear();
    
    display.setCursor(0, 0);
    
    display.print("123");
    display.setCursor(6,8);
    display.print("Hello World");   
    display.display();
    
    delay(500);
}
