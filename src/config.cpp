#include "config.h"

Config::Config()
{
    Serial.println("Default Config created.");
}

Config::Config(string configName, string name1, int count1, int weight1, string name2, int count2, int weight2, int loops)
{
    m_configName = configName;
    m_loops = loops;

    m_name1 = name1;
    m_count1 = count1;
    m_weight1 = weight1;

    m_name2 = name2;
    m_count2 = count2;
    m_weight2 = weight2;
}