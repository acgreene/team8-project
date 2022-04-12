
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>
#include <iostream>
#include <numeric>
#include <cmath>
#include "Frame.h"
#include "Person.h"
#include "Detector.h"
#include "Helpers.h"
#include "Connect.h"

Detector d;
#define INTERRUPT_PIN 25
bool interruptTable[64];

ESP_Client c;

void setup() {
//   Start Serial 
  Serial.begin(9600);
//
  pinMode(INTERRUPT_PIN, INPUT);
//
  d.g.setInterruptModeAbsolute();
  d.g.setUpperInterruptValueFahrenheit(80);
  d.g.setLowerInterruptValueFahrenheit(0);
  d.g.setInterruptHysteresisFahrenheit(5);
  d.g.interruptPinEnable();
//  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1);
  c.init();
  Serial.println("INIT");
  c.set_count(0);
  Serial.println("SET 0");

  // Give time to set up sensor and get out of frame for init step
//  delay(2000);

  // Initialize Background
//  Serial.println("About To Initialize");

//  esp_deep_sleep_start();
}


void loop() {

  while(!d.g.interruptFlagSet()){
    Serial.println("waiting for interrupt flag...");
    delay(500);
  }

  // tell the user that an interrupt was fired
  Serial.println("interrupt caught!");
  c.increment_count();
  Serial.println("INCREASED COUNT");

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
