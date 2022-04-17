#ifndef Detector_H
#define Detector_H

#include "Frame.h"
#include "Person.h"
#include "Helpers.h"
#include <SparkFun_GridEYE_Arduino_Library.h>
#include "ESP_Client.h"


class Detector{
public:
    void init(unsigned int num_frames);

    void update_and_process_frame();
    
    bool person_detected_mean();

    bool person_detected_otsu();

    void plot();

    void go_to_sleep();

    void wakeup();
    
    Detector();
    
    bool saw_past_person;
    bool sleeping;
    unsigned int num_consec_empty_frames;
    unsigned int count;
    double background_temp;
    double noise;
    Person past_person;
    GridEYE g;
    Frame curr_frame;
};


#endif
