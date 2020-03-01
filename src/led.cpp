#include <led.h>

int Led::ledCounter = 1;

Led::Led(int pin) : m_pin(pin)
{
    m_id = ledCounter++;

    pinMode(m_pin, OUTPUT);

    Serial.print("LED with id ");
    Serial.print(m_id);
    Serial.println(" created.");
}