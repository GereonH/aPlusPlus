#include "Arduino.h"
/**
 * Der String der momentanen Startseite. Ist hauptsächlich in html und bisschen css geschrieben
 */ 
const char startingSite[] PROGMEM = R"=====(
<html>
  
<head>
      <meta http-equiv=content-type content=text/html;charset=UTF-8>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <title>Startseite</title>
      <style> 
      html { 
        font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;
        }
        .button { 
          background-color: #4CAF50; border: none; color: white; padding: 16px 40px;
          text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;
        }
      </style>
</head>

<body>
  <h1> Prototype </h1>
  <p><a href=/1/config><button class=button>Konfiguration 1</button></a></p>
  <p><a href=/2/config><button class=button>Konfiguration 2</button></a></p>
  <p><a href=/3/config><button class=button>Konfiguration 3</button></a></p>
</body>
</html>
)=====";
