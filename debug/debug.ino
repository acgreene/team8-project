
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
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_pm.h>

//Detector d;
esp_pm_config_esp32_t pm_config;


#define INTERRUPT_PIN 25
bool interruptTable[64];
ESP_Client c;

void setup() {

  Serial.begin(9600);
  Serial.println("Setup");

  // Give time to set up sensor and get out of frame for init step
//  delay(3000);
//  esp_wifi_init();

  // Initialize Background
//  Serial.println("About To Initialize");
//  d.init(100);
  
  // Print Background Info
//  Serial.print("Background Temp: ");
//  Serial.println(d.background_temp);
//  Serial.print("Noise: ");
//  Serial.println(d.noise);
//  Serial.print("Detection Thresh: ");
//  Serial.println(d.background_temp + d.noise);
  
//  pinMode(INTERRUPT_PIN, INPUT);

//  d.g.setInterruptModeAbsolute();
//  float upper_lim = double(d.background_temp)/100.0 + 4*double(d.noise)/100.0; 
//  Serial.println(upper_lim);
//  d.g.setUpperInterruptValueFahrenheit(upper_lim);
//  d.g.setLowerInterruptValueFahrenheit(0);
//  d.g.setInterruptHysteresisFahrenheit(1);
//  d.g.interruptPinEnable();
//
//  esp_sleep_enable_timer_wakeup(1000000);
//  pm_config.max_freq_mhz = 240;
//  pm_config.min_freq_mhz = 80;
//  pm_config.light_sleep_enable = true;
//  
//  esp_pm_configure(&pm_config);
//  esp_wifi_set_ps(WIFI_PS_MIN_MODEM);
  // Maybe just lower CPU freq until someone is in frame
  
  // To skip unnecessary wake-up, you can consider initializing an esp_timer with the skip_unhandled_events option as true. 
  // Timers with this flag will not wake up the system and it helps to reduce consumption.
  c.init();
  WiFi.setSleep(true);
  setCpuFrequencyMhz(80);
}


void loop() {
//  Serial.println("Loop");
//  Serial.println("Entering Modem Sleep");
  
//  if(WiFi.status() != WL_CONNECTED){
//    Serial.println("Lost Connection");
//  }
//  WiFi.setSleep(false);
//  Serial.println("Exited Modem Sleep");
//  delay(1000);
  c.increment_count();
//  delay(1000);
  
//  Serial.println("Loop");
//  unsigned long start_time = millis();
//  for(int i = 0; i < 10; ++i){
//    ESP_Client c;
//    c.init();
//  }
//  unsigned long time_diff = millis() - start_time;
//  Serial.println(time_diff / 10.0);
//  delay(1000);
//  while(!d.g.interruptFlagSet()){
//    Serial.println("waiting for interrupt flag...");
//    delay(500);
//  }
//
//  // tell the user that an interrupt was fired
//  Serial.println("interrupt caught!");
//
//  // populate the interrupt flag table
//  for(int i = 0; i < 64; i++){
//    interruptTable[i] = d.g.pixelInterruptSet(i);    
//  }
//
//  // display the interrupt flag table
//    for(unsigned char i = 0; i < 64; i++){
//    Serial.print(interruptTable[i]);
//    Serial.print(" ");
//      if((i+1)%8==0){
//        Serial.println();
//      }
//    }
//  // clear the interrupt flag bit in the device register
//  d.g.clearInterruptFlag();
  
}
