// GPS Frequency Counter Example Sketch.
// Connect the 1 PPS signal to INT0 (D2 pin).
// Connect the input signal to be measured to T1 (D5 pin).
// The highest frequency the counter can measure is limited to about
// system clock frequency divided by 2.5, so about 6MHz with a
// 16MHz clock.

#include <Adafruit_SSD1306.h>
#include <gpsFreq.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

uint16_t nSample;
char strFreq[16];

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
}

void loop()
{
    if (!gpsFreq.isBusy)
    {
        if (nSample > 0)
        {
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setTextSize(2);
            
            display.setCursor(0, 0);

            //gpsFreq.formatFreq(strFreq);
            display.println(gpsFreq.freq);
            
            display.display();
        }
        
        ++nSample;
        
        gpsFreq.start(1);
    }
}
