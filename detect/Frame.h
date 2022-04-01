#ifndef Frame_h
#define Frame_h

#include <SparkFun_GridEYE_Arduino_Library.h>
#include "Helpers.h"
#include "Person.h"


class Frame{
public:
    void update_pixels(GridEYE &g);

    bool saw_person = false;
    double mean_temp;
    // Going to need array of people
    Person p;
    unsigned int table[8][8];
    
};

#endif /* Frame_h */
