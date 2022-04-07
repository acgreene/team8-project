
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>
#include <iostream>
#include <numeric>
#include <cmath>
#include "Frame.h"
#include "Person.h"
#include "Detector.h"
#include "Helpers.h"



double fill(unsigned target[][8], GridEYE &g){
    double mean = 0;
    for(byte row = 0; row < 8; ++row){
        for(byte col = 0; col < 8; ++col){
            target[row][col] = 100*g.getPixelTemperatureFahrenheit(row*8 + col);
            if(target[row][col] > 80000){
              Serial.print("X: ");
              Serial.print(col);
              Serial.print(" Y: ");
              Serial.println(row);
            }
            mean += target[row][col];
        }
    }
    mean /= 64.0;
}



Detector d;
  
void setup() {
  
  // Start Serial 
  Serial.begin(9600);

  // Give time to set up sensor and get out of frame for init step
  delay(2000);

  // Initialize Background
  Serial.println("About To Initialize");

  unsigned int num_frames = 30;
  float frames[num_frames][8][8];
  double frames_uint[num_frames][8][8];

  for(int i = 0; i < num_frames; ++i){
    for(byte row = 0; row < 8; ++row){
        for(byte col = 0; col < 8; ++col){
          frames[i][row][col] = d.g.getPixelTemperatureFahrenheit(row*8 + col);
          frames_uint[i][row][col] = (double) frames[i][row][col];
          Serial.print(frames[i][row][col]);
          Serial.print(" ");
          Serial.print(frames_uint[i][row][col]);
          Serial.print(" ");
        }
        Serial.println();
    }
    Serial.println();
  }
  
  
  

  for(int i = 0; i < num_frames; ++i){
     for(int j = 0; j < 8; ++j){
        for(int k = 0; k < 8; ++k){
          d.background_temp += frames[i][j][k];
        }
     }
  }

  d.background_temp /= double(num_frames*64);

   for(int i = 0; i < num_frames; ++i){
     for(int j = 0; j < 8; ++j){
        for(int k = 0; k < 8; ++k){
          d.noise += pow(frames[i][j][k] - d.background_temp, 2);
        }
     }
  }

  d.noise = sqrt(d.noise / double(num_frames*64));

  d.curr_frame.update_pixels(d.g);

  
  // Print Background Info
  Serial.print("Background Temp: ");
  Serial.println(d.background_temp);
  Serial.print("Noise: ");
  Serial.println(d.noise);
  Serial.print("Detection Thresh: ");
  Serial.println(d.background_temp + d.noise);

  // Delay for Update Frame
  delay(1000);
}


void loop() {

  //update current and past frame
//  d.update_frame();
//
//  double mean_hot = 0;
//  byte num_hot = 0;
//  double mean_cold = 0;
//  byte num_cold = 0;
//
//  for(byte row = 0; row < 8; ++row){
//    for(byte col = 0; col < 8; ++col){
//      if(d.curr_frame.table[row][col] > d.background_temp + d.noise){
//        mean_hot += d.curr_frame.table[row][col];
//        ++num_hot;
//      }
//      else{
//        mean_cold += d.curr_frame.table[row][col];
//        ++num_cold;
//      }
//    }
//  }
//
//  mean_hot /= double(num_hot);
//  mean_cold /= double(num_cold);
//
//  Serial.print("Mean Class Temp Diff: ");
//  Serial.println(mean_hot - mean_cold);
//  
//  delay(10);
}
