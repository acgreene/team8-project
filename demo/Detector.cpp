#include "Frame.h"
#include "Person.h"
#include "Helpers.h"
#include "Detector.h"
#include "ESP_Client.h"
#include <Wire.h>
#include <WiFi.h>
#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Arduino.h>

void Detector::init(unsigned int num_frames){

  unsigned int frames[num_frames][8][8];
  
  for(int i = 0; i < num_frames; ++i){
     double m = fill(frames[i], g);
     delay(100);
  }

  double num_good_pix = 0;
  
  for(int i = 0; i < num_frames; ++i){
     for(int j = 0; j < 8; ++j){
        for(int k = 0; k < 8; ++k){
          if(frames[i][j][k] < 10000){
            background_temp += frames[i][j][k];
            ++num_good_pix;
          }
        }
     }
  }

  background_temp /= num_good_pix;

   for(int i = 0; i < num_frames; ++i){
     for(int j = 0; j < 8; ++j){
        for(int k = 0; k < 8; ++k){
          if(frames[i][j][k] < 10000){
            noise += pow(frames[i][j][k] - background_temp, 2);
          }
        }
     }
  }
  noise = sqrt(noise / num_good_pix);
}
    

// Read in current frame, Assign old frame to curr frame
void Detector::update_and_process_frame(){

  // Assign current frame to past frame
  saw_past_person = curr_frame.saw_person;
  if(saw_past_person){
    past_person = curr_frame.p;
  }
  curr_frame.saw_person = false;

  double sum_hot = 0;
  double num_hot = 0;
  double sum_cold = 0;
  double num_cold = 0;

  byte x_max = 0;
  byte y_max = 0;
  unsigned int max_temp = 0;
  
  for(byte row = 0; row < 8; ++row){
      for(byte col = 0; col < 8; ++col){
          unsigned int pix_temp = (unsigned int) 100*g.getPixelTemperatureFahrenheit(row*8 + col);
          if(pix_temp > 10000){
            continue;
          }
          curr_frame.table[row][col] = pix_temp;

          if(pix_temp > max_temp){
            x_max = col;
            y_max = row;
            max_temp = pix_temp;
          }
          
          if(pix_temp > background_temp + 2*noise){
            sum_hot += pix_temp;
            ++num_hot;
          }
          else{
            sum_cold += pix_temp;
            ++num_cold;
          }
      }
   }

   curr_frame.diff_class_temp = (sum_hot / (num_hot + .1)) - (sum_cold / (num_cold + .1));
   curr_frame.mean_temp = (sum_hot + sum_cold) / (num_cold + num_hot);

   curr_frame.p.xpos = 7 - x_max; // reverse for plot
   curr_frame.p.ypos = y_max;

}


bool Detector::person_detected_mean(){
    // mean temp method
    return curr_frame.mean_temp > background_temp + noise;
}

bool Detector::person_detected_otsu(){
    return curr_frame.diff_class_temp > 3 * noise;
}

void Detector::plot(){
  for(int row = 0; row < 8; ++row){
    for(int col = 0; col < 8; ++col){
      if(row == curr_frame.p.ypos and col == curr_frame.p.xpos){
        Serial.print(" O ");
      }
      else{
        Serial.print(" . ");
      }
    }
    Serial.println();
  }
  Serial.println();
}

void Detector::go_to_sleep(){
  sleeping = true;
//  setCpuFrequencyMhz(80);
  WiFi.setSleep(true);
}

void Detector::wakeup(){
   sleeping = false;
//   setCpuFrequencyMhz(240);
   WiFi.setSleep(false);
}

Detector::Detector(){
  // Initialize GridEYE object
  g = GridEYE();
  Wire.begin();
  
  g.begin();
  g.setFramerate10FPS();

  count = 0;
  background_temp = 0;
  noise = 0;  
  saw_past_person = false;
  sleeping = false;
  num_consec_empty_frames = 0;
}

    
