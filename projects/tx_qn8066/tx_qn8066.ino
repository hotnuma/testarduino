#include <QN8066.h>
#define FREQUENCY 875

QN8066 tx;
bool detected = false;

void setup()
{
    delay(100);
    detected = tx.detectDevice();
    if (!detected)
        return;
    
    tx.setup(1, false, false, 0, 1);
    tx.setTX(FREQUENCY);
    tx.setPAC(56);
}

void loop()
{
    delay(500);
}


