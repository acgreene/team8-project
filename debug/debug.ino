
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>
#include <iostream>
#include <numeric>
#include <cmath>
#include "Frame.h"
#include "Person.h"
#include "Detector.h"
#include "Helpers.h"



double fill(unsigned int target[][8], GridEYE &g){
    double mean = 0;
    double num_good_pix = 0;
    for(byte row = 0; row < 8; ++row){
        for(byte col = 0; col < 8; ++col){
            target[row][col] = (unsigned int) 100*g.getPixelTemperatureFahrenheit(row*8 + col);
            if(target[row][col] < 10000){
              mean += target[row][col];
              ++num_good_pix;
            }
        }
    }
    return mean / num_good_pix;
}



Detector d;
#define INTERRUPT_PIN 25
bool interruptTable[64];
  
void setup() {
  
  // Start Serial 
  Serial.begin(9600);

  pinMode(INTERRUPT_PIN, INPUT);

  d.g.setInterruptModeAbsolute();
  d.g.setUpperInterruptValueFahrenheit(80);
  d.g.setLowerInterruptValueFahrenheit(0);
  d.g.setInterruptHysteresisFahrenheit(5);
  d.g.interruptPinEnable();
//  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1);

  // Give time to set up sensor and get out of frame for init step
//  delay(2000);

  // Initialize Background
  Serial.println("About To Initialize");

//  esp_deep_sleep_start();
}


void loop() {

  while(!d.g.interruptFlagSet()){
    Serial.println("waiting for interrupt flag...");
    delay(500);
  }

  // tell the user that an interrupt was fired
  Serial.println("interrupt caught!");

  // populate the interrupt flag table
  for(int i = 0; i < 64; i++){
    interruptTable[i] = d.g.pixelInterruptSet(i);    
  }

  // display the interrupt flag table
    for(unsigned char i = 0; i < 64; i++){
    Serial.print(interruptTable[i]);
    Serial.print(" ");
      if((i+1)%8==0){
        Serial.println();
      }
    }

  // clear the interrupt flag bit in the device register
  d.g.clearInterruptFlag();
  
}
