#include <SparkFun_GridEYE_Arduino_Library.h>
#include <iostream>
#include "Helpers.h"
#include "Frame.h"



void Frame::update_pixels(GridEYE &g){
   mean_temp = fill(table, g);
}

//  void printframe(unsigned int rate){
//      
//      for(unsigned char row = 0; row < 8; ++row){
//          for(unsigned char col = 0; col < 8; ++col){
//              Serial.print(table[row][col]);
//              Serial.print(" ");
//          }
//          Serial.println();
//      }
//      Serial.println();
//      Serial.println();
//      // print table every 'rate' ms
//      delay(rate);
//  }
  
//  Frame(){
//  
//    for(int i = 0; i < 8; ++i){
//      table[i] = (double*)malloc(8 * sizeof(double));
//    }
//  }
//  
//  ~Frame(){
//    for(int i = 0; i < 8; ++i){
//      free(table[i]);
//    }
