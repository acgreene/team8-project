#include "Frame.h"
#include "Person.h"
#include "Helpers.h"
#include "Detector.h"
#include <Wire.h>
#include <SparkFun_GridEYE_Arduino_Library.h>

void Detector::init(unsigned int num_frames){

  unsigned int frames[num_frames][8][8];
  
  for(int i = 0; i < num_frames; ++i){
     fill(frames[i], g);
     delay(100);
  }

  for(int i = 0; i < num_frames; ++i){
     for(int j = 0; j < 8; ++j){
        for(int k = 0; k < 8; ++k){
          background_temp += frames[i][j][k];
        }
     }
  }

  background_temp /= double(num_frames*64);

   for(int i = 0; i < num_frames; ++i){
     for(int j = 0; j < 8; ++j){
        for(int k = 0; k < 8; ++k){
          noise += pow(frames[i][j][k] - background_temp, 2);
        }
     }
  }

  noise = sqrt(noise / double(num_frames*64));

  curr_frame = new Frame();
  past_frame = new Frame();

  
  past_frame->update_pixels(g);
  delay(100);
  curr_frame->update_pixels(g);
}
    

  // Read in current frame, Assign old frame to curr frame
void Detector::update_frame(){
  past_frame->update_pixels(g);
  Frame *temp = past_frame;
  past_frame = curr_frame;
  curr_frame = temp;
}


  // TODO: Implement Otsu Bin or Histogram method. Don't know if this is the best implementation since we need to compute if a person is detected, then find how many people, then find where they are in separate steps. What if we could just scan the image for people and just get all three things at once??
bool Detector::person_detected(){
    
    // mean temp method
    return curr_frame->mean_temp > background_temp + noise;
    
}

void Detector::find_person(bool plotter){

  unsigned int max_temp = 0;
  int x_max = 0;
  int y_max = 0;
  // figure out their position
  for(int row = 0; row < 8; ++row){
    for(int col = 0; col < 8; ++col){
      if(curr_frame->table[row][col] > max_temp){
        max_temp = curr_frame->table[row][col];
        x_max = 7 - col;
        y_max = row;
      }
    }
  }

  if(plotter){
    for(int row = 0; row < 8; ++row){
      for(int col = 0; col < 8; ++col){
        if(row == int(y_max) and col == int(x_max)){
          Serial.print(" O ");
        }
        else{
          Serial.print(" . ");
        }
      }
      Serial.println();
    }
  }
  d.curr_frame->p.xpos = x_max;
  d.curr_frame->p.ypos = y_max;
  d.curr_frame->p.from_inside = x_max < 4; //VERIFY MY AXES ARE RIGHT
  
}


  // TODO: Update velocity directions given current and past frame
//void Detector::update_velocities();

Detector::Detector(){
  // Initialize GridEYE object
  g = GridEYE();
  Wire.begin();
  g.begin();
  g.setFramerate10FPS();

  count = 0;
  background_temp = 0;
  noise = 0;  
}
  
Detector::~Detector(){
  delete curr_frame;
  delete past_frame;
}

    
