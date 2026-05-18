#include <Adafruit_SSD1306.h>
#include <QN8066.h>

#define FREQUENCY 875

Adafruit_SSD1306 display(128, 64, &Wire, -1);
QN8066 tx;
bool detected = false;

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    delay(500);
    
    detected = tx.detectDevice();
    
    if (!detected)
        return;
    
    tx.setup(1,
             false,
             false,
             // PreEmphasis = 75
             1,
             // digital clock
             1);

    tx.setTX(FREQUENCY);
    tx.setPAC(56);
}

void loop()
{
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);

    display.setTextSize(2);
    if (detected)
        display.println("detected");
    else
        display.println("not detected");

    display.display();

    delay(500);
}


