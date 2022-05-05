#include <Adafruit_SSD1306.h>

// https://stackoverflow.com/questions/56266857/

Adafruit_SSD1306 display(128, 64, &Wire, -1);

float bat_read(int bat_pin, const float bat_min, const float bat_max)
{
    long val = analogRead(bat_pin);

    float voltage = (val * 5.0) / 1023.0;
    
    int output = ((voltage - bat_min) / (bat_max - bat_min)) * 5;
    
    return output;
}
void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop()
{
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.setTextSize(3);
    
    float bat_p = bat_read(A1, 2.0, 2.8);
    //display.println((int) bat_p / 5);
    display.println(bat_p);

    //long val = analogRead(A1);
    //display.println(val);
    
    display.display();
    
    delay(500);
}
