// GPS Frequency Counter Example Sketch.
// Connect the 1 PPS signal to INT0 (D2 pin).
// Connect the input signal to be measured to T1 (D5 pin).
// Connect a tactile button switch or similar from the D8 pin to
// ground. The highest frequency the counter can measure is limited to about
// system clock frequency divided by 2.5, so about 6MHz with a
// 16MHz clock.

#include <Adafruit_SSD1306.h>
#include <gpsFreq.h>
#include <JC_Button.h>

const uint8_t gateButton = 4;
const uint8_t gateLED = LED_BUILTIN;

uint16_t nSample;
bool gateLedState;
uint8_t gateTime {1};
char strFreq[16];
Button btnGate(gateButton);

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();

    pinMode(gateLED, OUTPUT);
    btnGate.begin();
    
    //lcd.begin(16, 2);
    //Serial.begin(115200);
    //Serial << F( "\n" __FILE__ "\n" __DATE__ " " __TIME__ "\n" );

    //lcd.clear();
    //lcd.setCursor(0, 1);
    //lcd << F("Gate: ") << gateTime << F(" sec");
}

void loop()
{
    btnGate.read();
    
    if (btnGate.wasReleased())
    {
        if (gateTime == 100)
            gateTime = 1;
        else
            gateTime *= 10;
        
        //Serial << F("Gate time: ") << gateTime << F(" sec") << endl;
        //lcd.setCursor(0, 1);
        //lcd << F("Gate: ") << gateTime << F(" sec  ");
    }

    if (!gpsFreq.isBusy)
    {
        if (nSample > 0)
        {
            gpsFreq.formatFreq(strFreq);
            
            //Serial << gpsFreq.ppsTotal << F(": ") << strFreq << F(" Hz") << endl;
            //lcd.clear();
            //lcd.setCursor(0, 0);
            //lcd << strFreq << F(" Hz");
            //lcd.setCursor(0, 1);
            //lcd << F("Gate: ") << gateTime << F(" sec");
            
            digitalWrite(gateLED, gateLedState = !gateLedState);
            
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setCursor(0, 0);
            
            display.setTextSize(2);
            display.println(strFreq);
            
            display.display();
            
            //delay(500);
       }
            ++nSample;
            gpsFreq.start(gateTime);
    }
}
