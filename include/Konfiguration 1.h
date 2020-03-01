#include "Arduino.h"
/**
 * Der String der momentanen Config1 Seite. Ist momentan in html, css und ganz wenig js geschrieben. Möglich das es nicht ganz klappt, da ich dort noch was versuche
 */ 
const char Konfiguration1[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  
<head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <title>Konfiguration 1</title>
      <style>
        html {
          font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;
       }
       .button { 
          background-color: #4CAF50; border: none; color: white; padding: 16px 40px;
          text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;
        }

  input[type=text], select {
  width: 100%;
  padding: 12px 20px;
  margin: 8px 0;
  display: inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing: border-box;
}

input[type=submit] {
  width: 100%;
  background-color: #4CAF50;
  color: white;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  border-radius: 4px;
  cursor: pointer;
}

input[type=submit]:hover {
  background-color: #45a049;
}

input[type=number] {
  width: 100%;
  padding: 14px 20px;
  margin: 8px 0;
  display:inline-block;
  border: 1px solid #ccc;
  border-radius: 4px;
  box-sizing:border-box;
  
}

div {
  border-radius: 5px;
  background-color: #f2f2f2;
  padding: 20px;
}
        
      
      </style>
</head>

<body>
    
  <h1> Konfiguration 1 </h1>
  <div>
  <form action="/get">
    Kiste 1: 
    <input id="name1" type="text" name="Kiste1">
    <br>
    Anzahl:
    <input id="count1" type="number" name="count1" min="0">
    <br>
    <br>
    Kiste 2:
    <input id="name2" type="text" name="Kiste2">
    <br>
    Anzahl:
    <input id="count2" type="number" name="count2" min="0">
    <br>
    <br>
    Wiederholungen:
    <input id="loops" type="number" name="loops" min="0">
    <br>
    <input type="submit" value="Speichern">
  </form>
  </div>
  <p><a href=/><button class=button>Zurück</button></a></p>
  




</body>
</html>
)=====";
