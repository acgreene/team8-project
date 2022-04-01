#ifndef Detector_H
#define Detector_H

#include "Frame.h"
#include "Person.h"
#include "Helpers.h"
#include <SparkFun_GridEYE_Arduino_Library.h>



class Detector{
public:
    void init(unsigned int num_frames);

    void update_frame();
    
    bool person_detected();

    void find_person(bool plotter);
    
    void update_velocities();
    
    Detector();
    
    ~Detector();
    
    unsigned int count;
    double background_temp;
    double noise;
    GridEYE g;
    Frame *curr_frame;
    Frame *past_frame;
};


#endif
