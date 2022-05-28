#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

static const int TXPin = 4, RXPin = 3;
//static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.display();
    
    //Serial.begin(115200);
    
    ss.begin(9600);
}

void loop()
{
    // This sketch displays information every time a new sentence is correctly encoded.
    
    while (ss.available() > 0)
        if (gps.encode(ss.read()))
            displayInfo();
    
    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
        display.println("No GPS detected: check wiring.");
        
        while(true);
    }
}

void displayInfo()
{
    display.clearDisplay();
    
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(2);
    
    if (gps.location.isValid())
    {
        display.print(gps.location.lat());
        display.print(" : ");
        display.println(gps.location.lng());
        
    }
    else
    {
        display.println("Invalid...");
    }
    
    //Serial.print(F("  Date/Time: "));
    
    if (gps.date.isValid())
    {
        //Serial.print(gps.date.month());
        //Serial.print(F("/"));
        //Serial.print(gps.date.day());
        //Serial.print(F("/"));
        //Serial.print(gps.date.year());
    }
    else
    {
        //Serial.print(F("INVALID"));
    }
    
    //Serial.print(F(" "));
    
    if (gps.time.isValid())
    {
        //if (gps.time.hour() < 10)
            //Serial.print(F("0"));
        
        //Serial.print(gps.time.hour());
        //Serial.print(F(":"));
        
        //if (gps.time.minute() < 10)
        //    Serial.print(F("0"));
        //Serial.print(gps.time.minute());
        //Serial.print(F(":"));
        
        //if (gps.time.second() < 10)
        //    Serial.print(F("0"));
        
        //Serial.print(gps.time.second());
        //Serial.print(F("."));
        
        //if (gps.time.centisecond() < 10)
        //    Serial.print(F("0"));
            
        //Serial.print(gps.time.centisecond());
    }
    else
    {
        //Serial.print(F("INVALID"));
    }
    
    //Serial.println();
    
    display.display();

}
