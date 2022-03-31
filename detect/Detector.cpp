#include "Frame.h"
#include "Person.h"
#include "helpers.cpp"




struct Detector{
  
    // TODO: Fix body to be compatible with new code structure, use helpers::fill_pixel for each frame. Should update background mean and noise member variables
    void init_background(unsigned int num_frames){
      
        double frames[num_frames][8][8] = {0};
        
        for(int i = 0; i < num_frames; ++i){
           fill_pixels(frames[i], g);
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
    }
        
   
    
    // TODO: Implement Otsu Bin or Histogram method. Don't know if this is the best implementation since we need to compute if a person is detected, then find how many people, then find where they are in separate steps. What if we could just scan the image for people and just get all three things at once??
    bool person_detected(){
        
        // mean temp method
        return curr_frame.mean_temp > background_temp + noise / 8.0;
        
    }
    
    // TODO: Update velocity directions given current and past frame
    void update_velocities();

    Detector(unsigned int num_frames){
      // Initialize GridEYE object
      g = GridEye();
      grideye.begin();
      grideye.setFramerate10FPS();

      count = 0;
      background_temp = 0;
      noise = 0;

      init_background(num_frames);

      curr_frame.update_pixels(g);
      
    }
    
    unsigned int count;
    double background_temp;
    double noise;
    // Going to need array of detected people, probably dynamically allocated
    Person p;
    GridEye g;
    Frame curr_frame;
    Frame past_frame;
};
