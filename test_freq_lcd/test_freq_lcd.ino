// GPS Frequency Counter Example Sketch.
// Connect the 1 PPS signal to INT0 (D2 pin).
// Connect the input signal to be measured to T1 (D5 pin).
// The highest frequency the counter can measure is limited to about
// system clock frequency divided by 2.5, so about 6MHz with a
// 16MHz clock.

#include <LiquidCrystal_I2C.h>
#include <gpsFreq.h>

uint16_t nSample;
char strFreq[16];

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
}

void loop()
{
    if (!gpsFreq.isBusy)
    {
        if (nSample > 0)
        {

            
            lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
            
            //lcd.print("Hello World!"); // Print the string "Hello World!"
            
            //gpsFreq.formatFreq(strFreq);
            lcd.print(gpsFreq.freq);
            
            lcd.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
            lcd.print("LCD tutorial");

        }
        
        ++nSample;
        
        gpsFreq.start(1);
    }
}
