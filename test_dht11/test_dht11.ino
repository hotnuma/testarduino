#include <Adafruit_SSD1306.h>
#include <SimpleDHT.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
SimpleDHT11 dht11;

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
}

void loop()
{
    byte th = 0;
    byte hm = 0;
    
    int err = SimpleDHTErrSuccess;
    
    if ((err = dht11.read(8, &th, &hm, NULL)) != SimpleDHTErrSuccess) 
        return;
    
    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    
    display.print("Th ");
    display.print((int) th);
    display.println(" C");
    
    display.print("Hm ");
    display.print((int) hm);
    display.println(" %");
    
    display.display();
    
    delay(1500);
}
