#include <SparkFun_GridEYE_Arduino_Library.h>
#include <iostream>
#include "Helpers.h"
#include "Frame.h"



//void Frame::update_pixels(GridEYE &g){
//
//    double mean_hot = 0;
//    double num_hot = 0;
//    double mean_cold = 0;
//    double num_cold = 0;
//
//    byte x_max = 0;
//    byte y_max = 0;
//    unsigned int max_temp = 0;
//    
//    for(byte row = 0; row < 8; ++row){
//        for(byte col = 0; col < 8; ++col){
//            unsigned int pix_temp = 100*g.getPixelTemperatureFahrenheit(row*8 + col);
//            table[row][col] = pix_temp;
//
//            if(pix_temp > max_temp){
//              x_max = col;
//              y_max = row;
//              max_temp = pix_temp;
//            }
//            
//            if(pix_temp > thresh){
//              mean_hot += pix_temp;
//              ++num_hot;
//            }
//            else{
//              mean_cold += pix_temp;
//              ++num_cold;
//            }
//        }
//    }
//    return mean / 64.0;
//  
//   mean_temp, diff_class_temp = fill(table, g);
//}

void Frame::print_frame(unsigned int rate){
      
      for(unsigned char row = 0; row < 8; ++row){
          for(unsigned char col = 0; col < 8; ++col){
              Serial.print(table[row][col]);
              Serial.print(" ");
          }
          Serial.println();
      }
      Serial.println();
      Serial.println();
      // print table every 'rate' ms
      delay(rate);
  }
