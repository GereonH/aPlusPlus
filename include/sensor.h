#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor
{
private:
    /**
     * A fix calibration distance.
     */
    double m_calibrationDistance = 0;
    /**
     * Distance the sensor is measuring right now. Calculated through: (duration / 2) * 0.03432.
     */
    double m_sensorDistance;
    /**
     * Id of sensor.
     */
    int m_id;
    /**
     * Trigger and echo pins of sensor.
     */
    const int m_triggerPin, m_echoPin;
    /**
     * Time it takes for the sensor to send a signal and receive it back.
     */
    int m_duration;

public:
    /**
     * Sensor counter to determine sensor id.
     */
    static int sensorCounter;

    /**
     * Constructor of sensor.
     */
    Sensor(int triggerPin, int echoPin);
    /**
     * Deconstructor of sensor.
     */
    ~Sensor() {}

    double getCalibrationDistance() const { return m_calibrationDistance; }

    void setCalibrationDistance(double distance)
    {
        m_calibrationDistance = distance;
    }

    double getSensorDistance() const { return m_sensorDistance; }
    /**
     * Distance sensor is measuring in cm. Calcuated through: (duration / 2) * 0.03432
     */
    void setSensorDistance(int duration) { m_sensorDistance = (duration / 2) * 0.03432; }

    int getId() const { return m_id; }

    int getTriggerPin() const { return m_triggerPin; }

    int getEchoPin() const { return m_echoPin; }

    int getDuration() const { return m_duration; }
    void setDuration(int duration) { m_duration = duration; }
    /**
     * Whole calibration process of one sensor.
     */
    void calibrate();
    /**
     * Process for measuring distance for one sensor.
     */
    void measureDistance();
    /**
     * This method iterates through the array of all sensors and sets the sensor calibration for each.
     * @brief Sets sensor calibration for all arrays.
     * @param allSensors Array of all sensors.
     */
    static void calibrateAll(Sensor sensorArr[]); // TODO

    void printDistance();
};

#endif // SENSOR_H--