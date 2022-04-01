#include "Helpers.h"
#include <SparkFun_GridEYE_Arduino_Library.h>

double fill(unsigned target[][8], GridEYE &g){
    double mean = 0;
    for(unsigned char row = 0; row < 8; ++row){
        for(unsigned char col = 0; col < 8; ++col){
            target[row][col] = 100*g.getPixelTemperatureFahrenheit(row*8 + col);
            mean += target[row][col];
        }
    }
    return mean / 64.0;
}
