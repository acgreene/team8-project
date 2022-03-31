#ifndef FRAME_H
#define FRAME_H

#include "Frame.h"
#include "Person.h"
#include "helpers.cpp"

struct Detector{
  
    void init_background(unsigned int num_frames);
    
    bool person_detected();
    
    void update_velocities();
    
    Detector(unsigned int num_frames);
    
    unsigned int count;
    double background_temp;
    double noise;
    // Going to need array of detected people, probably dynamically allocated
    Person p;
    Grideye g;
    Frame curr_frame;
    Frame past_frame;
};




#endif // FRAME_H
