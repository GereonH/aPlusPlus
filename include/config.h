#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <string>

using namespace std;

class Config
{
private:
    std::string m_configName = "";
    int m_loops = 0;

    string m_name1 = "";
    int m_count1 = 0;
    int m_weight1 = 0;

    string m_name2 = "";
    int m_count2 = 0;
    int m_weight2 = 0;

public:
    Config();
    Config(string configName, string name1, int count1, int weight1, string name2, int count2, int weight2, int loops);
    ~Config() {}

    void setConfigName(string configName)
    {
        m_configName = configName;
    }

    string getConfigName()
    {
        return m_configName;
    }

    void setLoops(int loops)
    {
        m_loops = loops;
    }

    int getLoops()
    {
        return m_loops;
    }

    void setCount1(int count1)
    {
        m_count1 = count1;
    }

    void setCount2(int count2)
    {
        m_count2 = count2;
    }

    string getName1()
    {
        return m_name1;
    }

    int getCount1()
    {
        return m_count1;
    }

    int getWeight1()
    {
        return m_weight1;
    }

    string getName2()
    {
        return m_name2;
    }

    int getCount2()
    {
        return m_count2;
    }

    int getWeight2()
    {
        return m_weight2;
    }
};

#endif // CONFIG_H--
