#define d1 125
#define d2 1000

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(d1);
    digitalWrite(LED_BUILTIN, LOW);
    delay(d1);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(d1);
    digitalWrite(LED_BUILTIN, LOW);
    delay(d2);
}
