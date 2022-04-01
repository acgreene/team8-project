
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>
#include <iostream>
#include <numeric>
#include <cmath>
#include "Frame.h"
#include "Person.h"
#include "Detector.h"
#include "Helpers.h"

Detector d;
  
void setup() {
  
  // Start Serial 
  Serial.begin(9600);

  // Give time to set up sensor and get out of frame for init step
  delay(5000);

  // Initialize Background
  Serial.println("About To Initialize");
  d.init(100);

  // Make sure values are resonable, sometimes they are crazy large, probably due to some uninitialized memory or weird comms
  while(d.background_temp > 8000){
    Serial.println("Init Failed, Trying Again...");
    d.init(100);
    
  }
  
  // Print Background Info
  Serial.print("Background Temp: ");
  Serial.println(d.background_temp);
  Serial.print("Noise: ");
  Serial.println(d.noise);
  Serial.print("Detection Thresh: ");
  Serial.println(d.background_temp + d.noise / 2.0);

  // Delay for Update Frame
  delay(1000);
}

void loop() {

  //update current and past frame
  d.update_frame();
  
  // check for person in frame
  if(d.person_detected()){

    // Set Saw Person Flag to True for This Frame
    d.curr_frame->saw_person = true;

    // Find Person Location and Update Important Info
    // Need to Verify Axis Orientation for each Sensor Setup
    d.find_person(false);
    

    if(past_frame.saw_person){
        // figure out if this is a new person or same person
        // update velocity direction
    }

    else{

      // Assign new person
      // Velocity found from which direction they entered
    }    
  }
  else{
    // Check if someone was in last frame, meaning that they left the frame
    if(past_frame.saw_person){
      if(past_frame.p->from_inside and !past_frame.p->moving_inside){
        --count;
      }
      else if(!past_frame.p->from_inside and past_frame.p->moving_inside){
        ++count;
      }
    }
  }

  // Give Time For Sensor To Supply new Frame
  delay(100);
}
