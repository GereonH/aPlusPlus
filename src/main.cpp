#include "sensor.h"
#include "led.h"
#include "state.h"
#include "config.h"
#include "Website.h"
#include "Konfiguration 1.h"
#include "Konfiguration 2.h"
#include "Konfiguration 3.h"

#include <Arduino.h>
#include <ArduinoJson.h>
#include <HX711.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPAsyncWebServer.h>

using namespace std;

// variables for ultrasonic sensor 1
Led red_led1(27);
Led green_led1(23);

Led red_led2(19);
Led green_led2(18);

// Sensor(Trigger, Echo);
Sensor sensor1(33, 32);
Sensor sensor2(16, 17);
float sensorCalibrationFactor = 0.75;

Sensor sensorArr[2] = {sensor1, sensor2};

// Configs:
string config1Name = "Konfig1";
string item1Name = "Mutter";
int item1Count = 2;
int item1Weight = 20;
string item2Name = "Schraube";
int item2Count = 2;
int item2Weight = 30;
int config1Loops = 1;

State currentState;
Config config1(config1Name, item1Name, item1Count, item1Weight, item2Name, item2Count, item2Weight, config1Loops);

// scale:
const int LOADCELL_DOUT_PIN = 25;
const int LOADCELL_SCK_PIN = 26;
HX711 scale;
float tareWeight;
float weight;

bool tempArr[4];

// WiFi Setup:
/**
 * @param ssid ssid ist der Name des Netzwerkes mit dem sich das Gerät verbinden muss
 * @param password Das dazugehörige Passwort
 */
const char* ssid = "Ambos++";
const char* password = "Diakonie123";

AsyncWebServer server(80);

const char* NAME_VALUE_1 = "Kiste1";
const char* NAME_VALUE_2 = "Kiste2";
const char* COUNT_VALUE_1 = "count1";
const char* COUNT_VALUE_2 = "count2";
const char* LOOPS = "loops";

void saveLedSettings() {
  // save current setting of LEDs
  tempArr[0] = red_led1.isLedOn();
  tempArr[1] = green_led1.isLedOn();
  tempArr[2] = red_led2.isLedOn();
  tempArr[3] = green_led2.isLedOn();
}

void loadLedSettings() {
  // resume to previous setting of LEDs
  tempArr[0] ? red_led1.ledOn() : red_led1.ledOff();
  tempArr[1] ? green_led1.ledOn() : green_led1.ledOff();
  tempArr[2] ? red_led2.ledOn() : red_led2.ledOff();
  tempArr[3] ? green_led2.ledOn() : green_led2.ledOff();
}

void reduceCurrentItemByOne(){
  currentState.setCurrentItemCount(currentState.getCurrentItemCount() - 1);
  saveLedSettings();
  green_led1.ledOff();
  green_led2.ledOff();
  delay(50);
  green_led1.ledOn();
  green_led2.ledOn();
  delay(50);
  loadLedSettings();
}

void turnAllLEDsOff(){
  green_led1.ledOff();
  red_led1.ledOff();
  green_led2.ledOff();
  red_led2.ledOff();
}

void runningLEDs() {
    turnAllLEDsOff();
    green_led1.ledOn();
    delay(300);
    green_led1.ledOff();
    red_led1.ledOn();
    delay(300);
    red_led1.ledOff();
    green_led2.ledOn();
    delay(300);
    green_led2.ledOff();
    red_led2.ledOn();
    delay(500);
    red_led2.ledOff();
    green_led2.ledOn();
    delay(300);
    green_led2.ledOff();
    red_led1.ledOn();
    delay(300);
    red_led1.ledOff();
    green_led1.ledOn();
    delay(500);
}

// 0 = no significant weight change
// 1 = positive significant weight change
// -1 = negative significant weight change
int hasSignificantWeightChange() {
  float refWeight1 = currentState.getCurrentWeight();
  delay(1000);
  float refWeight2 = scale.get_units(1);
  if(refWeight2 > refWeight1 + 0.5) {
    currentState.setReferenceWeight(refWeight2);
    return 1;
  } else if (refWeight2 < refWeight1 - 0.25) {
    currentState.setReferenceWeight(refWeight2);
    return -1;
  } else {
    return 0;
  }
}

bool hasAdditionalItemOnScale(){
  if(hasSignificantWeightChange() == 1) {
    return true;
  } else {
    return false;
  }
}

void setup()
{
  Serial.begin(115200);

  WiFi.mode(WIFI_AP); //WIFI_AP um einzustellen das es ein Access Point ist
  IPAddress IP = WiFi.softAP(ssid, password); //Die IP-Adresse des AP, kann beim Sevicemonitor abgelesen
  WiFi.begin(ssid, password); //Start des Netzwerks
  Serial.println("");

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", startingSite);
  }); //Startseite, heißt momentan nur Website
  server.on("/1/config", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", Konfiguration1);
  }); //Konfig1 wenn man einen bestimmten Button drückt, führt zu einer Seite die momentan als Konfiguration 1 eingespeichert ist
  server.on("/2/config", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", Konfiguration2);
  }); //Dasselbe wie bei Konfig1, nur eine andere Seite
  server.on("/3/config", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", Konfiguration3);
  }); //Dasselbe wie bei Konfig1, nur eine andere Seite
  
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {

    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(NAME_VALUE_1)) {
      item1Name = request->getParam(NAME_VALUE_1)->value();
      inputParamName1 = NAME_VALUE_1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
     if (request->hasParam(NAME_VALUE_2)) {
      inputMessageName2 = request->getParam(NAME_VALUE_2)->value();
      inputParamName2 = NAME_VALUE_2;
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
     if (request->hasParam(COUNT_VALUE_1)) {
      inputMessageCount1 = request->getParam(COUNT_VALUE_1)->value();
      inputParamCount1 = COUNT_VALUE_1;
    }

     if (request->hasParam(COUNT_VALUE_2)) {
      inputMessageCount2 = request->getParam(COUNT_VALUE_2)->value();
      inputParamCount2 = COUNT_VALUE_2;
    }
    
    if (request->hasParam(LOOPS)) {
      inputMessageLoops = request->getParam(LOOPS)->value();
      inputParamLoops = LOOPS;
    }
    
    Serial.print(inputParamName1.c_str());
    request->send(200, "text/html", "Konfiguration Erfolgreich gespeichert!" 
                                      "<br><a href=http://192.168.4.1//>Return to Home Page</a>");
  });

  server.begin(); 


  green_led1.ledOn();
  red_led1.ledOn();
  green_led2.ledOn();
  red_led2.ledOn();

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();
  Serial.println("Scale tared.");
  float scaleCalibration_factor = 385.5;
  scale.set_scale(scaleCalibration_factor);
  currentState.setTareWeight(scale.get_units(5));
  currentState.setReferenceWeight(currentState.getTareWeight());

  currentState.loadCurrentConfig(config1);

  // Calibration of all sensors
  sensor1.calibrate();
  sensor2.calibrate();


  turnAllLEDsOff();
}


void loop()
{
  Serial.print(inputMessageName1.c_str());
  Serial.print(inputMessageLoops.c_str());
  currentState.setCurrentWeight(scale.get_units(2));

  // // data from ultrasonic sensors
  sensor1.measureDistance();
  sensor2.measureDistance();

  // check for box 1
  if (
        sensor1.getSensorDistance() < sensor1.getCalibrationDistance() * sensorCalibrationFactor 
        && !currentState.getIsItem1DoneForLoop())
  {
    green_led2.ledOff();
    green_led1.ledOn();
    red_led1.ledOff();
    currentState.setCurrentItem(item1Name, item1Count, 1);
  }
  // check for box 2
  else if (
        sensor2.getSensorDistance() < sensor2.getCalibrationDistance() * sensorCalibrationFactor 
        && !currentState.getIsItem2DoneForLoop())
  {
    green_led1.ledOff();
    green_led2.ledOn();
    red_led2.ledOff();
    currentState.setCurrentItem(item2Name, item2Count, 2);
  }
  // if both items are done for the loop and both sensors are blocked, skip to next loop.
  else if (
      sensor1.getSensorDistance() < sensor1.getCalibrationDistance() * sensorCalibrationFactor 
      && currentState.getIsItem1DoneForLoop() 
      && sensor2.getSensorDistance() < sensor2.getCalibrationDistance() * sensorCalibrationFactor 
      && currentState.getIsItem2DoneForLoop())
  {
    red_led1.ledOn();
    red_led2.ledOn();
    green_led1.ledOn();
    green_led2.ledOn();
    
    delay(2000);
    
    green_led1.ledOff();
    delay(500);    
    red_led1.ledOff();
    delay(500);
    green_led2.ledOff();
    delay(500);
    red_led2.ledOff();
    delay(500);
    currentState.nextLoop();
  }

  if(currentState.getLoopCount() == 0 ) {
    runningLEDs();
  }

  // only prints if box is active 
  if (currentState.getActiveBoxId() != 0)
  {
    if (currentState.getCurrentItemCount() == 0)
    {
      if (currentState.getActiveBoxId() == 1)
      {
        red_led1.ledOn();
        green_led1.ledOff();
        currentState.setIsItem1DoneForLoop(true);
      }
      else if (currentState.getActiveBoxId() == 2)
      {
        red_led2.ledOn();
        green_led2.ledOff();
        currentState.setIsItem2DoneForLoop(true);
      }
    }

    if(hasAdditionalItemOnScale()) {
      if(currentState.getCurrentItemCount() > 0) {
        reduceCurrentItemByOne();
      } else if (currentState.getCurrentItemCount() == 0) {

        saveLedSettings();

        while(hasSignificantWeightChange() != -1){
          red_led1.ledOn();
          red_led2.ledOn();
          delay(150);
          red_led1.ledOff();
          red_led2.ledOff();
          currentState.setCurrentWeight(scale.get_units(2));
        }
        loadLedSettings();
      }
    }
    currentState.printCurrentState();

  }


  // Testing:
  // currentState.printWeight();
  // red_led1.ledOn();
  // green_led1.ledOn();
  // sensor1.printDistance();
  // red_led2.ledOn();
  // green_led2.ledOn();
  // sensor2.printDistance();


  // delay for measurements in milliseconds
  delay(50);
}
