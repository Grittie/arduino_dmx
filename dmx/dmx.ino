#include "Ultrasonic.h"
#include <DmxSimple.h>

Ultrasonic ultrasonic(4);

boolean switchState = false;

unsigned long toggleTime = 1000;
unsigned long last_triggered = millis();

void setup()
{
    Serial.begin(9600);
    DmxSimple.usePin(2);
}

void loop()
{
    long RangeInCentimeters;

    if ((millis() - last_triggered) > toggleTime)
    {
        RangeInCentimeters = ultrasonic.MeasureInCentimeters();
        char buf[100];
        
        sprintf(buf, "%ld", last_triggered);
        Serial.println(buf);

        if (RangeInCentimeters < 50)
        {

            if (switchState)
            {
                DmxSimple.write(1, 0);
                DmxSimple.write(2, 255);
            }
            else
            {
                DmxSimple.write(1, 255);
                DmxSimple.write(2, 0);
            }
            switchState = !switchState;
            last_triggered = millis();
            delay(100);
        }
    }
}
