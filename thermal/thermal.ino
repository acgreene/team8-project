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
   Documentation: https://github.com/adafruit/Adafruit_AMG88xx/blob/master/Adafruit_AMG88xx.cpp
*/
#include <Adafruit_AMG88xx.h>

/**
   Adafruit_GFX is a code library

   Library: https://learn.adafruit.com/adafruit-gfx-graphics-library
   Documentation: https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.cpp
*/
#include <Adafruit_GFX.h>


#include <Adafruit_ST7735.h>

// declare functions that are written at end of code.
void printPixels();

// create an instance of the amg8833 thermal camera.
Adafruit_AMG88xx amg;

// create an array to store all of the pixels the amg detects.
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];

void setup() {

  // opens serial port, sets data rate to 9600 bits/sec (baud)
  Serial.begin(9600);
  Serial.println(F("AMG88xx test"));

  bool status;

  // initialize the amg thermal cam, defaults I2C address to 0x69.
  status = amg.begin();

  // checks if the amg is connected to the esp32.
  if (!status) {
    Serial.println("Could not find the amg, check wiring");
    while (1);
  }

  // allow the amg to boot up before asking for data.
  delay(100);
}

void loop() {

  // continuously read the pixels output by the amg.
  amg.readPixels(pixels);

}

/**
   Input: none.
   Output: none.
   Effect: Prints all of the pixels currently being output by the amg to the serial monitor.
*/
void printPixels() {
  Serial.println();
  Serial.print("[");
  for (int i = 1; i <= AMG88xx_PIXEL_ARRAY_SIZE; i++) {
    Serial.print(pixels[i - 1]);
    Serial.print(", ");
    if ( i % 8 == 0 ) Serial.println();
  }
  Serial.println("]");
  Serial.println();

  // delay 500ms.
  delay(500);
}
