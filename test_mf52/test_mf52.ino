#include <Adafruit_SSD1306.h>

#define BUFFSIZE 5
int index = 0;
uint16_t buff[BUFFSIZE] = {0};
uint16_t sum = 0;
uint16_t value = 0;
uint16_t result = 0;

const float T0 = 25 + 273.15;
const float RT0 = 10000.0;
const float R0 = 10000.0;
const float B = 3435.0;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

float readTemp(float val)
{
    return (1 / ((1/T0) + (1/B) * log((R0/RT0) * ((1024.0/val) - 1))) - 273.15);
}

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    for (int i = 0; i < BUFFSIZE; ++i)
    {
        buff[i] = analogRead(A0);
        sum += buff[i];
        delay(100);
    }
}

void loop()
{
    // Remove the oldest entry from the sum
    sum = sum - buff[index];
    
    value = analogRead(A0);
    buff[index] = value;
    sum = sum + value;
    
    // Increment the index, and wrap to 0 if it exceeds the window size
    index = (index+1) % BUFFSIZE;
    
    result = sum / BUFFSIZE;
    
    //float T = 1 / ((1/T0) + (1/B)*log((R0/RT0)*((1024.0/Result) - 1))) - 273.15;

    float temp = readTemp(result);

    display.clearDisplay();

    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(5, 5);
    
    display.print("Te ");
    display.print(temp);
    display.println(" C");
    
    display.display();
    
    delay(500);
}
