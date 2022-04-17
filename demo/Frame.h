#ifndef Frame_h
#define Frame_h

#include <SparkFun_GridEYE_Arduino_Library.h>
#include "Helpers.h"
#include "Person.h"


class Frame{
public:

    void print_frame(unsigned int rate);
    
    bool saw_person = false;
    double mean_temp;
    double diff_class_temp;
    Person p;
    unsigned int table[8][8];
    
};

#endif /* Frame_h */
