#ifndef FRAME_H
#define FRAME_H

#include <SparkFun_GridEYE_Arduino_Library.h>
#include <iostream>
#include "helpers.cpp"

struct Frame {
    
    void update_pixels(const GridEYE &g);
    
    void print(unsigned int rate);
    
    double table[8][8];
    double mean_temp;
};

#endif // FRAME_H
