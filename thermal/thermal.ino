/******************************************
  EECS 300 Team 8
  Adafruit AMG8833 Thermal Camera Sensor Code
 ******************************************/

/**
  AMG thermal cam uses I2C communications protocol to communicate.
  When connected to esp32 it will return an array of 64 individual
  infrared temperature readings over I2C. The Wire library allows
  us to communicate with I2C devices. 

  I2C reading: https://en.wikipedia.org/wiki/I²C
  Wire library: https://www.arduino.cc/en/reference/wire
 */
#include <Wire.h>

/**
 Adafruit_AMG88xx is the code library we can use to interface
 with the sensor. 

 Library: https://www.arduino.cc/reference/en/libraries/adafruit-amg88xx-library/
 Documentation: https://github.com/adafruit/Adafruit_AMG88xx/blob/master/Adafruit_AMG88xx.h
 */
#include <Adafruit_AMG88xx.h>

// create an instance of the amg8833 thermal camera. 
Adafruit_AMG88xx amg;

void setup() {

  // opens serial port, sets data rate to 9600 bits/sec (baud)
  Serial.begin(9600);
  Serial.println(F("AMG88xx test"));

  bool status;
    
  // initialize the amg thermal cam
  status = amg.begin();
  if (!status) {
    Serial.println("Could not find the amg, check wiring");
    while (1);
  }

}

void loop() {
  

}
