#include <Adafruit_SSD1306.h>
#include <Adafruit_MCP9808.h>

#define BUFFSIZE 5
int index = 0;
float buff[BUFFSIZE] = {0};
float sum = 0;
float value = 0;
float result = 0;

Adafruit_SSD1306 display(128, 64, &Wire, -1);
Adafruit_MCP9808 sensor;

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    
    if (!sensor.begin())
        return;
    
    sensors_event_t event; 
    sensor.getEvent(&event);
    value = event.temperature;

    for (int i = 0; i < BUFFSIZE; ++i)
    {
        buff[i] = value;
        sum += buff[i];
    }
}

void loop()
{
    // Remove the oldest entry from the sum
    sum = sum - buff[index];
    
    sensors_event_t event; 
    sensor.getEvent(&event);
    value = event.temperature;

    buff[index] = value;
    sum = sum + value;
    
    // Increment the index, and wrap to 0 if it exceeds the window size
    index = (index+1) % BUFFSIZE;
    
    result = sum / BUFFSIZE;
    
    display.clearDisplay();

    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.setCursor(0, 0);
    
    display.print("Te ");
    display.print(result);
    display.println(" C");
    
    display.display();
    
    yield();
    delay(500);
}
