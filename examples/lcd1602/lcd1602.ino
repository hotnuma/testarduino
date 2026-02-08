#include <LiquidCrystal_I2C.h>

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup()
{
    lcd.init();
    lcd.backlight();
}

void loop()
{
    lcd.setCursor(2, 0);
    lcd.print("Hello World!");
    lcd.setCursor(2, 1);
    lcd.print("LCD tutorial");
}
