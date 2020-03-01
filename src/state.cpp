#include "state.h"

State::State()
{
    Serial.println("State initiated.");
}

void State::loadCurrentConfig(Config config)
{
    m_currentConfig = config;
    m_currentConfigName = m_currentConfig.getConfigName();
    m_loopCount = m_currentConfig.getLoops();
    Serial.println("Config loaded.");
}

void State::setCurrentItem(string itemName, int itemCount, int activeBoxId)
{
    m_currentItemName = itemName;
    m_currentItemCount = itemCount;
    m_currentItemMaxCount = itemCount;
    m_activeBoxId = activeBoxId;
}

void State::nextLoop()
{
    m_loopCount--;
    m_isItem1DoneForLoop = false;
    m_isItem2DoneForLoop = false;
    m_activeBoxId = 0;
}

void State::printCurrentState()
{
    printConfig();
    printWeight();
}

void State::printWeight(){
    Serial.println("");
    Serial.println("Scale:");
    Serial.print("TareWeight: ");
    Serial.print(m_tareWeight);
    Serial.print(" - ReferenceWeight: ");
    Serial.print(m_referenceWeight);
    Serial.print(" - CurrentWeight: ");
    Serial.println(m_currentWeight);
}

void State::printUltrasonicSensors(){
    Serial.println("\n");

}

void State::printConfig(){
    Serial.println("");
    Serial.print("ConfigName: ");
    Serial.print(m_currentConfigName.c_str());
    Serial.print(" - activeBox: ");
    Serial.print(m_activeBoxId);
    Serial.print(" - Loops left: ");
    Serial.println(m_loopCount);
    Serial.print("currentItemName: ");
    Serial.print(m_currentItemName.c_str());
    Serial.print(" - currentItemCount: ");
    Serial.print(m_currentItemCount);
    Serial.print("/");
    Serial.println(m_currentItemMaxCount);
    Serial.print("IsItem1DoneForLoop: ");
    Serial.print(m_isItem1DoneForLoop ? "true" : "flase");
    Serial.print(" - IsItem2DoneForLoop: ");
    Serial.println(m_isItem2DoneForLoop ? "true" : "flase");
}