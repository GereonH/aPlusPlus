#include "sensor.h"

/**
 * Sensor counter for sensor id.
 */
int Sensor::sensorCounter = 1;

Sensor::Sensor(int triggerPin, int echoPin) // fully initialised??
    : m_triggerPin(triggerPin),
      m_echoPin(echoPin)
{
  m_sensorDistance = 0;

  m_id = sensorCounter++;
}

void Sensor::calibrateAll(Sensor sensorArr[])
{
  for (int i = 0; i < sensorCounter - 1; i++)
  {
    Serial.print("Sensor: ");
    Serial.println(sensorArr[i].getId());
    sensorArr[i].calibrate();
  }
}

void Sensor::calibrate()
{
  pinMode(this->getTriggerPin(), OUTPUT);
  pinMode(this->getEchoPin(), INPUT);

  Serial.print("CALIBRATING");
  double helperSum = 0;
  int loops = 20;
  for (int i = 1; i <= loops; i++)
  {
    this->measureDistance();
    Serial.print(".");
    if (i >= 10)
    {
      helperSum += this->getDuration();
    }
    delay(100);
  }
  m_calibrationDistance = ((helperSum / (loops - 10)) / 2) * 0.03432;

  Serial.println(".");
  Serial.print("Calibration finished. Calibration distance is: ");
  Serial.println(this->getCalibrationDistance());
}

void Sensor::measureDistance()
{
  digitalWrite(this->getTriggerPin(), LOW);
  delay(5);
  digitalWrite(this->getTriggerPin(), HIGH);
  delay(10);
  digitalWrite(this->getTriggerPin(), LOW);
  this->setDuration(pulseIn(this->getEchoPin(), HIGH));
  this->setSensorDistance(this->getDuration());
}

void Sensor::printDistance()
{

  if (m_sensorDistance >= 500 || m_sensorDistance <= 0)
  {
    Serial.println("Kein Messwert");
  }
  Serial.print("+++++++++ ");
  Serial.print(m_sensorDistance);
  Serial.print(" cm  ");
  Serial.print("+++++++++ ");
  Serial.print(m_calibrationDistance);
  Serial.println(" cm");
}