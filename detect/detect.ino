
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>
#include <iostream>
#include <numeric>
#include <cmath>
#include "Frame.h"
#include "Person.h"
#include "Detector.h"

GridEYE grideye;

void setup() {

  // Start your preferred I2C object 
  Wire.begin();

  // Initialize GridEYE object
  grideye.begin();
  grideye.setFramerate10FPS();
  
  // Pour a bowl of serial
  Serial.begin(115200);

  // Construct Detector Object
  Detector d;

  // Initialize Background
  d.init(200);
  
}

void loop() {

}
