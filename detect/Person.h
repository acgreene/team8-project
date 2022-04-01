#ifndef Person_H
#define Person_H

struct Person{
    
    double xpos = 0;
    double ypos = 0;
    double temp;
    unsigned long detected_time;
    bool from_inside;
    bool moving_inside;
};

#endif
