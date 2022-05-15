const bool blink = false;               // set to true to blink an LED
const uint8_t blinkLED = LED_BUILTIN;   // the pin number of the LED to blink
const uint32_t blinkInterval = 1000;    // blink interval, milliseconds

void setup()
{
    if (blink)
        pinMode(blinkLED, OUTPUT);
        
    // D11, MOSI, PB3, DIP 17
    pinMode(MOSI, OUTPUT);

    // Set timer 2 to output a 1MHz square wave on MOSI (D11 on Arduino Uno)
    
    // stop timer 2
    TCCR2B = 0;
    
    // CTC mode, toggle OC2A on compare match
    TCCR2A = _BV(WGM21) | _BV(COM2A0);
    
    // calculate OCR2A value for Timer 2. For 16MHz, divide by 8,
    // else assume 8MHz and divide by 4.
    const uint32_t cpuFreq = F_CPU;
    OCR2A = (cpuFreq == 16000000) ? 7 : 3;
    
    TCCR2B = _BV(CS20);                     // start timer 2, no prescaling
}

void loop()
{
    if (blink)
    {
        static uint32_t ms;
        static uint32_t msLast;
        static bool ledState;

        ms = millis();
        
        if (ms - msLast >= blinkInterval)
        {
            msLast = ms;
            digitalWrite(blinkLED, ledState = !ledState);
        }
    }
}
