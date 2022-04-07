/*
  Using the Panasonic Grid-EYE Sensor
  By: Nick Poole
  SparkFun Electronics
  Date: January 12th, 2018
  
  MIT License: Permission is hereby granted, free of charge, to any person obtaining a copy of this 
  software and associated documentation files (the "Software"), to deal in the Software without 
  restriction, including without limitation the rights to use, copy, modify, merge, publish, 
  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or 
  substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  
  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14568
  
  This example implements a rudimentary heat camera in the serial terminal, using a matrix of ascii
  characters to represent the temperature of each pixel in the device. Start your terminal at 115200 
  and make the window as small as possible for best effect.
  
  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the sensor onto the shield
*/

#include <SparkFun_GridEYE_Arduino_Library.h>
#include <Wire.h>
#include <iostream>
#include <numeric>
#include <cmath>

// Use these values (in degrees C) to adjust the contrast
#define HOT 40
#define COLD 20
#define NUM_FRAMES 200
// This table can be of type int because we map the pixel 
// temperature to 0-3. Temperatures are reported by the 
// library as floats
double pixelTable[64];
double frames[NUM_FRAMES][64];
double mean[64] = {};
double stdv[64] = {};
double backgroundAvg;

GridEYE grideye;

void updatePixelTable() {
  // loop through all 64 pixels on the device and map each float value to a number
  // between 0 and 3 using the HOT and COLD values we set at the top of the sketch
  for(unsigned char i = 0; i < 64; i++){
    // pixelTable[i] = map(grideye.getPixelTemperature(i), COLD, HOT, 0, 3);
      pixelTable[i] = grideye.getPixelTemperatureFahrenheit(i);
  }
}

//function finds the moving avg of pixelTable for a period of i and returns it
void stats(double num_frames) {

  for(int j = 0; j < 64; ++j){
    mean[j] = 0;
    stdv[j] = 0;
  }
  
  for(int j=0; j<num_frames; j++) {
    //update pixelTable for every frame in pd i
    updatePixelTable();
    //find sum of pixels in pixelTable() using std::accumulate
    // sum = std::accumulate(std::begin(pixelTable), std::end(pixelTable), 0, std::plus<double>());
    // movingAvg.push_back(sum/64);
    for(int k = 0; k < 64; ++k){
      frames[j][k] = pixelTable[k]; //copies the kth val in pixelTable
    }
  }
  for(int j = 0; j < 64; ++j){
    for(int k = 0; k < 100; ++k){
        mean[j] += frames[k][j] / 100.0;
    }
  }

  for(int j = 0; j < 64; ++j){
    for(int k = 0; k < 100; ++k){
        stdv[j] += pow((frames[k][j] - mean[j]),2) / 100.0;
    }
    stdv[j] = sqrt(stdv[j]);
  }
  return;
}

void setup() {

  // Start your preferred I2C object 
  Wire.begin();
  // Library assumes "Wire" for I2C but you can pass something else with begin() if you like
  grideye.begin();
  grideye.setFramerate10FPS();
  // Pour a bowl of serial
  Serial.begin(115200);
  // Serial.println("Background temp = \n");
  stats(100);
  
//  Serial.println();
//  Serial.println("Mean Image: ");
//  for(unsigned char i = 0; i < 64; i++){
//    Serial.print(mean[i]);
//    Serial.print(" ");
//    if((i+1)%8==0){
//      Serial.println();
//    }
//  }
//  backgroundAvg = std::accumulate(std::begin(mean), std::end(mean), 0, std::plus<double>())/64.0;
//  Serial.println();
//  Serial.println("Standard Deviation: ");
//  double tot_std = 0;
//  for(unsigned char i = 0; i < 64; i++){
//    tot_std += stdv[i];
//  }
//  tot_std /= 64;
//  Serial.println(tot_std);
}

void loop() {
  updatePixelTable(); //initialize pixel temperatures
//  if(inFrame(backgroundAvg)) {
//    Serial.println("--------------");
//    Serial.println("HUMAN DETECTED");
//    Serial.println("--------------");
//  }
  printPixelTable(500); //print table every 0.5sec
  
  /* Framerate Test Calculation Code
  double avg_fps = 0;
  for(int i = 0; i < 100; ++i){
    double init = grideye.getPixelTemperatureFahrenheit(0);
    int start = millis();
    bool cont = true;
    while(cont){
      updatePixelTable();
      if(pixelTable[0] != init) cont = false;
    }
    int endt = millis();
    double fps = 1000.0 / (endt - start);
    avg_fps += fps / 100.0;
  }
  Serial.println(avg_fps);
  */
}


/* 
Function: Loop through the table of mapped values and print a character corresponding to each
pixel's temperature in an 8x8 grid.
Input: Rate of print in ms. 
Output: An 8x8 table of pixel values in the serial monitor. 
*/ 
void printPixelTable(int rate) {
  for(unsigned char i = 0; i < 64; i++){
    Serial.print(pixelTable[i]);
    Serial.print(" ");
    if((i+1)%8==0){
//      Serial.print(" ]");
      Serial.println();
//      Serial.print("[ ")
    }
  }
  // in between updates, throw a few linefeeds to visually separate the grids. If you're using
  // a serial terminal outside the Arduino IDE, you can replace these linefeeds with a clearscreen
  // command
  Serial.println();
//  Serial.println();

  // print table every 'rate' ms
  delay(rate);
}

/*
Overloaded function based on a pixel threshold for determining if someone is in frame
*/
bool inFrame(int temp_threshold, int num_pix_thresh) {
  int num_hot = 0;
  for(int k = 0; k < 64; ++k){
      if(pixelTable[k] > temp_threshold){
        ++num_hot;
      }
      if(num_hot == num_pix_thresh){
        return true;
      }
    }
    return false;
}
/*
Function: Finds if someone is in the frame of the camera. 
Input: a double indicating the threshold temperature for human detection. 
Output: a boolean value, true if someone is in frame, false if not. 
*/
bool inFrame(double threshold) {
  int i = 0;
  while(i < 64 && pixelTable[i] <= threshold) {
    i++;
  }
  if(i < 64) return true;
  else return false;
}

/*
Function: Finds the number of people in the frame of the camera. 
Input: n/a
Output: a boolean value, true if someone is in frame, false if not. 
*/
int peopleInFrame() {
  //lmaooo gl making this func
}

//represents a coordinate position in the camera frame. 
struct pos {
  int x;
  int y;
};
