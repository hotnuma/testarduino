#include <Adafruit_SSD1306.h>
#include <Adafruit_ADS1X15.h>

Adafruit_SSD1306 display(128, 64, &Wire, 4);
Adafruit_ADS1115 ads;

//=======================================================================
void setup() 
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay(); 
    
    //analogReference(INTERNAL);
    
    ads.begin();
}

//======================================================================
void loop() 
{
    int16_t adc0 = ads.readADC_SingleEnded(0);
    
    float Vadc0 = ads.computeVolts(adc0);
    
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.clearDisplay();
    display.setCursor(0,0);
    
    display.println(adc0);
    display.println(Vadc0);
    
    display.display();
    
    delay(100);
}
