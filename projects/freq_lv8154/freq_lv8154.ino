#include "Arduino.h"
#include "counter.h"
#include "shiftreg.h"
#include "math.h"

ShiftRegIC shift;
CounterIC counter(&shift);

uint32_t tf;
uint32_t t0_1;
uint32_t t0_2;

void setup()
{
	counter.init(48, 50, 52, 53);

	shift.CLK_pin = 40;
	shift.QH_pin = 22;
	shift.SHLD_pin = 38;
	shift.set_clock_freq(1000);
	shift.init();

	Serial.begin(115200);
	tf = millis();
	t0_1 = millis();
	t0_2 = millis();
}

void loop()
{
	counter.update();

	if (Serial.available() > 0)
    {
		uint8_t in_byte = Serial.read();

		// Spacebar input gets Counter A and B values and prints to serial terminal
		if (in_byte == 0x20)
        {
			uint32_t countsA = counter.readCounter("A");
			uint32_t countsB = counter.readCounter("B");
			Serial.println("*******************************");
			Serial.print("Counts on A: ");
			Serial.println(countsA);
			Serial.print("Counts on B: ");
			Serial.println(countsB);
			Serial.println();
			Serial.print("Elapsed time since last check: ");
			Serial.print((tf-t0_1)/1000.0, 3);
			Serial.println(" sec");
			Serial.print("Expected Counts on A: ");
			Serial.println((int) floor(counter.a_freq*(tf-t0_2)/1000.0));
			Serial.print("Expected Counts on B: ");
			Serial.println((int) floor(counter.b_freq*(tf-t0_2)/1000.0));
			Serial.println();
			t0_1 = millis();
		}

		// "c" input clears the counters
		else if (in_byte == 0x63)
        {
			Serial.println("Counters cleared!");
			
            counter.clearCounters();
			
            t0_2 = millis();
		}

		// "i" input gets status of counter A overflow
		else if (in_byte == 0x69)
        {
			Serial.print("Counter A overflow status: ");
			
            if (counter.overFlow())
				Serial.print("True");
			else
				Serial.print("False");
		}

		// "t" input toggles counter B on/off
		else if (in_byte == 0x74)
        {
			counter.toggleCounterB();
			
            if (counter.enabledCounterB())
				Serial.println("Counter B ON");
			else
				Serial.println("Counter B OFF");
		}


	}

	tf = millis();

}

