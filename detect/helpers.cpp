#include "Helpers.h"
#include <SparkFun_GridEYE_Arduino_Library.h>



double fill(unsigned int target[][8], GridEYE &g){
    double mean = 0;
    for(byte row = 0; row < 8; ++row){
        for(byte col = 0; col < 8; ++col){
            target[row][col] = (unsigned int) 100*g.getPixelTemperatureFahrenheit(row*8 + col);
            mean += target[row][col];
        }
    }
    return mean / 64.0;
}

int sgn(int x){
  if(x < 0){
    return -1;
  }
  else if(x > 0){
    return 1;
  }
  return 0;
}
