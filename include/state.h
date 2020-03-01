#ifndef STATE_H
#define STATE_H

#include "config.h"

#include <Arduino.h>

using namespace std;

class State
{

private:
    Config m_currentConfig;

    string m_currentConfigName = "";

    string m_currentItemName = "";

    int m_currentItemCount = 0;

    int m_currentItemMaxCount = 0;

    bool m_isItem1DoneForLoop = false;
    bool m_isItem2DoneForLoop = false;

    int m_activeBoxId = 0;

    int m_loopCount = 0;

    float m_tareWeight = 0;

    float m_referenceWeight = 0;

    float m_currentWeight = 0;

public:
    State();
    ~State() {}

    void loadCurrentConfig(Config config);

    void setCurrentItem(string itemName, int itemCount, int activeBoxId);

    void nextLoop();

    void printCurrentState();

    void printWeight();

    void printUltrasonicSensors();

    void printConfig();

    // ##################################

    string getCurrentConfigName() const
    {
        return m_currentConfigName;
    }

    void setCurrentItemName(string currentItemName)
    {
        m_currentConfigName = currentItemName;
    }

    string getCurrentItemName() const
    {
        return m_currentItemName;
    }

    void setCurrentItemCount(int currentItemCount)
    {
        m_currentItemCount = currentItemCount;
    }

    int getCurrentItemCount() const
    {
        return m_currentItemCount;
    }

    void setIsItem1DoneForLoop(bool isDone)
    {
        m_isItem1DoneForLoop = isDone;
    }

    bool getIsItem1DoneForLoop() const
    {
        return m_isItem1DoneForLoop;
    }

    void setIsItem2DoneForLoop(bool isDone)
    {
        m_isItem2DoneForLoop = isDone;
    }

    bool getIsItem2DoneForLoop() const
    {
        return m_isItem2DoneForLoop;
    }

    void setLoopCount(int loopCount)
    {
        m_loopCount = loopCount;
    }

    int getLoopCount() const
    {
        return m_loopCount;
    }

    int getActiveBoxId() const
    {
        return m_activeBoxId;
    }

    int getCurrentItemMaxCount() const
    {
        return m_currentItemMaxCount;
    }

    void setTareWeight(float tareWeight) {
        m_tareWeight = tareWeight;
    }

    float getTareWeight() const {
        return m_tareWeight;
    }

    void setReferenceWeight(float referenceWeight) {
        m_referenceWeight = referenceWeight;
    }

    float getReferenceWeight() const {
        return m_referenceWeight;
    }

    void setCurrentWeight(float currentWeight) {
        m_currentWeight = currentWeight;
    }

    float getCurrentWeight() const {
        return m_currentWeight;
    }
};

#endif // STATE_H--