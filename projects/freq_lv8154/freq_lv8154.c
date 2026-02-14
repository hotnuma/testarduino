

#include <LiquidCrystal_I2C.h>
#include <avr/io.h>

#define NUMCHARS 16
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, NUMCHARS, 2);

char strFreq[NUMCHARS + 1] = {0};

char SetRegister(char registerNumber)
{
    DDRC |= 0b00001111; // set A0-A3 as outputs
    switch (registerNumber)
    {
    case (3):
        PORTC = 0b00000111; // A3
        break;
    case (2):
        PORTC = 0b00001011; // A2
        break;
    case (1):
        PORTC = 0b00001101; // A1
        break;
    case (0):
        PORTC = 0b00001110; // A0
        break;
    }
}

int ReadRegister(char registerNumber)
{
    SetRegister(registerNumber);

    // set inputs
    DDRC &= ~(1 << PC4);
    DDRC &= ~(1 << PC5);

    DDRD &= ~(1 << PD2);
    DDRD &= ~(1 << PD3);
    DDRD &= ~(1 << PD4);
    DDRD &= ~(1 << PD5);
    DDRD &= ~(1 << PD6);
    DDRD &= ~(1 << PD7);

    int value = 0;

    if ((PINC & (1 << PC4)))
        value |= 0b00000001;

    if ((PINC & (1 << PC5)))
        value |= 0b00000010;

    if ((PIND & (1 << PD2)))
        value |= 0b00000100;

    if ((PIND & (1 << PD3)))
        value |= 0b00001000;

    if ((PIND & (1 << PD4)))
        value |= 0b00010000;

    if ((PIND & (1 << PD5)))
        value |= 0b00100000;

    if ((PIND & (1 << PD6)))
        value |= 0b01000000;

    if ((PIND & (1 << PD7)))
        value |= 0b10000000;

    return value;
}

uint32_t ReadCount()
{
    uint32_t value = 0;

    value += ReadRegister(3);
    value = value << 8;

    value += ReadRegister(2);
    value = value << 8;

    value += ReadRegister(1);
    value = value << 8;

    value += ReadRegister(0);

    return value;

    //SerialSendLongASCII(value);
    //SerialSendBreak();
}

void setup()
{
    lcd.init();
    lcd.backlight();
}

void loop()
{
    //~ if (gpsFreq.isBusy)
        //~ return;

    lcd.clear();

    //gpsFreq.formatFreq(strFreq);
    lcd.setCursor(2, 0);
    lcd.print(strFreq);

    //gpsFreq.start(1);
}


