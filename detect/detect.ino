
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

// TODO: 
// Enter a deep sleep when nobody is in the frame and set up Interrupt to wake the device when someone enters
// Will need to reconnect Wifi and BT each time we wake
// Hold Overall count in Server ESP, Client ESP just sends +1 or -1 each time


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
    
    if(d.past_frame.saw_person){
        // figure out if this is a new person or same person
        // maybe consider using velocity info
        int x_dist = d.curr_frame->p.xpos - d.past_frame->xpos;
        int y_dist = d.curr_frame->p.ypos - d.past_frame->ypos;
        int dist = x_dist*x_dist + y_dist*y_dist
        // If blobs are close, we conclude it is the same person
        if(dist <  5){
          // update velocity direction if they moved
          if(x_dist != 0){
            d.curr_frame->p.moving_inside = x_dist < 0;
          }
          // Keep track of where they entered
          d.curr_frame->p.from_inside = d.past_frame->p.from_inside;
        }
        else{
          // update count since person left the frame
          if(past_frame.p->from_inside and !past_frame.p->moving_inside){
            --count;
          }
          else if(!past_frame.p->from_inside and past_frame.p->moving_inside){
            ++count;
          }
        }
    }
    else{
      // Assign new person
      // Velocity found from which direction they entered
      d->curr_frame.p.from_inside = d->curr_frame.p->xpos < 4;
      d->curr_frame.p.moving_inside = !d->curr_frame.p->from_inside;
    }    
  }
  // Nobody Seen in Current Frame
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

    // MAYBE CONSIDER ADAPTIVE BACKGROUND UPDATE
    
  }

  // Give Time For Sensor To Supply new Frame
  // CONSIDER CHANGING THIS TO A SLEEP COMMAND TO REDUCE POWER
  delay(100);
}
