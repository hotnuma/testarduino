#include <Adafruit_SSD1306.h>
#include <FreqCount.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.display();
    
    //lcd.begin(16, 2);// LCD 16X2
    
    pinMode(7, INPUT);
    
    FreqCount.begin(1000);
}

unsigned long f;
void loop()
{
    //display.println("1234567890");
    
    
    
    if (FreqCount.available())
    { 
        f = FreqCount.read(); 
        
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println(f);
        display.display();
    }
    

    delay(1000);
    
    //lcd.clear();
}
