# microstation_grow_automated
Automate  microgreens and hydroponics vertical rack system 


❤️🍀🌱 "Working Progress" 🍀🌱❤️

### Description:
  The principal Idea is to create an open source vertical automated vegetable rack system, to grow microgreens in a cocofiber with humus sustrate, and also grow aromatics baby leaf plants with ebb and flood hydroponics system.
  I would like this rack can be a principal node to get all the data from differents species and them comunicate with other racks and send the same automation depending of the 

### Harware:

* Arduino Mkr1010.
* Arduino uno.
* Rasberry pi 3.
* Shield Protoboard Protoshield Arduino Uno
* three, 5 volts relay.
* 2 Lm2596 Step-down Dc-dc 1,23-35v 3a Display.
* 1 Sparkfun Logic Level Converter - Bi-directional
* 1 power suply 12 volt, 10 amperes.
* Riel dims for the 220volt led light system cables.
* 4 220 volts led light panels.
* terminals block to separete 3v/5v/12v
* 4 coolers pwm 4 wires.
* 4 capacitive Soil Moisture Sensor v1.2.
* 2 water temperature level Ds18b20.
* 4 Electrovalvules 12 volt.
* 1 12v submersible waterpump
* 1 12v diaphragm waterpump
* 2 dht22 ambient and temperature sensors.
* 2 digital water level arduino sensors.
* 2 20 liters black tanks, one for the microgreens irrigation system, and another for the hydroponics baby leaf system.
* 8 Polypropylene trays 1020 for microgreens. 
* 2 Polypropylene trays 57 cm x 36 cm x 6 cm for hydroponics system.
* Polypropylene tube 1/2 for irrigation system with pressure connectors without using glue.
* microtubes for irrigation system 
* stainless steel rack 


### Automation with arduino:

the automation sytem was tested with and arduino mkr1010 using the ntpclient library to get the time and do the automations. and the Arduino uno was conected via serial with a logic Level Converter to the arduino mkr1010 that sends over serial comunication, data to the arduino uno in order to automate lights and coolers.
Using this setting I was experimenting sometimes an out of sync of the hour and, even some wifi disconections problems, I try to fix the code, but I am still testing this settings.



 ### Automation with mqtt message using python:
 
 the system can be automated with an external sofware running in the raspberry pi with all the logics made in a python sofware, sending data over mqtt to the arduino mkr1010.
 
 Here I am making an API with Fastapi and python to created automations and a crud system to (created-read-deleted-updated),and get and save data from diferents racks, and send over mqtt intructions to the automation sofware or directly to the mkr1010.
 
 Now I want to developed an automation sofware for desktop using python and QT6. and also I would like to implement home assistant sofware to test it.
 
 
  ### the cocofiber microgreens irrigation systems :
  
  this automations works with an daily routime getting the data form the capacitive Soil Moisture Sensor v1.2 on separeted trays with differents species, and analysing this data and doing a calibration to get the better values of humydity and them depending of the results the irrigations system will work or not, doing separetd irrigations over the trays.
  




