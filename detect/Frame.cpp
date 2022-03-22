#include <SparkFun_GridEYE_Arduino_Library.h>
#include <iostream>
#include "helpers.cpp"

struct Frame {
    
    void update_pixels(const GridEYE &g){
        mean_temp = fill_pixels(table, g);
    }

    void print(unsigned int rate){
        
        for(unsigned char row = 0; row < 8; ++row){
            for(unsigned char col = 0; col < 8; ++col){
                Serial.print(pixelTable[i]);
                Serial.print(" ");
            }
            Serial.print(" ]")
            Serial.println();
            Serial.print("[ ")
        }
        Serial.println();
        Serial.println();
        // print table every 'rate' ms
        delay(rate);
    }
    
    double table[8][8];
    double mean_temp;
};
