#ifndef FRAME_H
#define FRAME_H

#include <SparkFun_GridEYE_Arduino_Library.h>
#include <iostream>

struct Frame {
    
    void update_pixels(Const GridEYE &g);
    
    void print(unsigned int rate);
    
    double table[8][8];
};

#endif // FRAME_H
