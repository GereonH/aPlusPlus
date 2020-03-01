#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led
{
private:
    const int m_pin = 0;
    bool m_isOn = false;

    int m_id;

public:
    static int ledCounter;

    Led(int pin);
    ~Led(){};

    void ledOn()
    {
        digitalWrite(m_pin, HIGH);
        m_isOn = true;
    }

    void ledOff()
    {
        digitalWrite(m_pin, LOW);
        m_isOn = false;
    }

    // ####################

    int getPin() const
    {
        return m_pin;
    }

    int getId() const
    {
        return m_id;
    }

    bool isLedOn() const {
        return m_isOn;
    }


};

#endif // LED_H--