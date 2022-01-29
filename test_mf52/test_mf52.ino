//#define SSD1306_NO_SPLASH 1

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
    Serial.begin(9600);
    
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    
    display.display();
    delay(2000); // Pause for 2 seconds
}

void loop()
{
    const float T0 = 25 + 273.15;
    const float RT0 = 10000.0;
    const float R0 = 10000.0;
    const float B = 3135.0;

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
    
    delay(250);
}
