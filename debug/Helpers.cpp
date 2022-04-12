#include "Helpers.h"
#include <SparkFun_GridEYE_Arduino_Library.h>



double fill(unsigned int target[][8], GridEYE &g){
    double mean = 0;
    double num_good_pix = 0;
    for(byte row = 0; row < 8; ++row){
        for(byte col = 0; col < 8; ++col){
            target[row][col] = (unsigned int) 100*g.getPixelTemperatureFahrenheit(row*8 + col);
            if(target[row][col] < 10000){
              mean += target[row][col];
              ++num_good_pix;
            }
        }
    }
    return mean / num_good_pix;
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
