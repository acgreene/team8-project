
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>
#include <WiFi.h>
#include <iostream>
#include <numeric>
#include <cmath>
#include "Frame.h"
#include "Person.h"
#include "Detector.h"
#include "Helpers.h"
#include "ESP_Client.h"


INTERRUPT_PIN = 25;
Detector d;

void setup() {
  
  // Start Serial 
  Serial.begin(9600);

  d.c.init();
  Serial.println("Connected to Server");

  // Give time to set up sensor and get out of frame for init step
  delay(3000);

  // Initialize Background
  Serial.println("About To Initialize");
  d.init(100);
  
  // Print Background Info
  Serial.print("Background Temp: ");
  Serial.println(d.background_temp);
  Serial.print("Noise: ");
  Serial.println(d.noise);
  Serial.print("Detection Thresh: ");
  Serial.println(d.background_temp + d.noise);

  // Delay for Update Frame
  delay(100);
}

// TODO: 
// Enter a deep sleep when nobody is in the frame and set up Interrupt to wake the device when someone enters
// Will need to reconnect Wifi or BT each time we wake
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html
// Hold Overall count in Server ESP, Client ESP just sends +1 or -1 each time


void loop() {

  //update current and past frame
  // Reads in new frame
  // Gets mean temp and mean class diff
  // Finds position of hottest pixel and updates x and y positions in curr_frame.p
  d.update_and_process_frame();
  
  // check for person in frame
  if(d.person_detected_mean() or d.person_detected_otsu()){
    
    // Set Saw Person Flag to True for This Frame
    d.curr_frame.saw_person = true;

    // Plots Table to Serial
    d.plot();
    
    if(d.saw_past_person){
      
        // figure out if this is a new person or same person
        int x_dist = d.curr_frame.p.xpos - d.past_person.xpos;
        
        // If blobs are close or along momentum vector, we conclude it is the same person
        if(abs(x_dist) <  4 or sgn(x_dist) == sgn(d.past_person.num_steps_right)){
          
          // Keep track of where they entered
          d.curr_frame.p.from_inside = d.past_person.from_inside;
          d.curr_frame.p.num_steps_right = d.past_person.num_steps_right + sgn(x_dist);
        }
        else{
          Serial.println("DOUBLE SWITCH");
          Serial.println("NEED TO FIGURE THIS OUT");
        }
    }
    else{
      // Assign new person
      // Velocity found from which direction they entered
      Serial.println("NEW PERSON FOUND");
      d.curr_frame.p.from_inside = d.curr_frame.p.xpos < 4;
      d.curr_frame.p.num_steps_right = d.curr_frame.p.from_inside ? 1 : -1;
      if(d.curr_frame.p.from_inside){
        Serial.println("CAME FROM INSIDE");
      }
      else{
        Serial.println("CAME FROM OUTISDE");
      } 
    }
 }
//  // Nobody Seen in Current Frame
  else{
    // Check if someone was in last frame, meaning that they left the frame
    if(d.saw_past_person){
      if(d.past_person.from_inside and d.past_person.xpos >= 4){
        Serial.println("LEAVING ROOM");
        Serial.println("Occupancy Count Decreased by 1");
        --d.count;
        d.c.decrement_count();
      }
      else if(!d.past_person.from_inside and d.past_person.xpos < 4){
        Serial.println("ENTERING ROOM");
        Serial.println("Occupancy Count Increased by 1");
        ++d.count;
        d.c.increment_count();
      }
      else{
        Serial.println("LEFT THE WAY THEY CAME");
        Serial.println("No Change to Occupancy Count");
      }
    }

    // MAYBE CONSIDER ADAPTIVE BACKGROUND UPDATE
    
  }

  // Give Time For Sensor To Supply new Frame
  delay(10);
}
