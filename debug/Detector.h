#ifndef Detector_H
#define Detector_H

#include "Frame.h"
#include "Person.h"
#include "Helpers.h"
#include <SparkFun_GridEYE_Arduino_Library.h>



class Detector{
public:
//    int init(unsigned int num_frames);

//    void update_frame();
    
    bool person_detected();

    void find_person(bool plotter);
    
    void update_velocities();
    
    Detector();
    
//    ~Detector();

    bool saw_past_person;
    unsigned int count;
    double background_temp;
    double noise;
    Person past_person;
    GridEYE g;
    Frame curr_frame;
};


#endif
