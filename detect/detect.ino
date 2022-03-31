
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>
#include <iostream>
#include <numeric>
#include <cmath>
#include "Frame.h"
#include "Person.h"
#include "Detector.h"

void setup() {

  // Start your preferred I2C object 
  Wire.begin();
  
  // Start Serial 
  Serial.begin(115200);

  // Construct Detector Object
  Detector d = Detector(200);
}

void loop() {

  // read in new frame
  // set past frame to curr frame

  // look for person

}
