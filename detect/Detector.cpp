#include "Frame.h"
#include "Person.h"
#include "helpers.cpp"




struct Detector{
  
    // TODO: Fix body to be compatible with new code structure, use helpers::fill_pixel for each frame. Should update background mean and noise member variables
    void init(unsigned int num_frames){
        double frames[num_frames][8][8] = {0};
        
//        for(int frame = 0; frame < num_frames; ++frame){
//            //update pixelTable for every frame in pd i
//            updatePixelTable();
//            // find sum of pixels in pixelTable() using std::accumulate
//            // sum = std::accumulate(std::begin(pixelTable), std::end(pixelTable), 0, std::plus<double>());
//            // movingAvg.push_back(sum/64);
//            for(int k = 0; k < 64; ++k){
//                frames[j][k] = pixelTable[k]; //copies the kth val in pixelTable
//            }
//        }
//        for(int j = 0; j < 64; ++j){
//            for(int k = 0; k < 100; ++k){
//                mean[j] += frames[k][j] / 100.0;
//            }
//        }
//
//        for(int j = 0; j < 64; ++j){
//            for(int k = 0; k < 100; ++k){
//                stdv[j] += pow((frames[k][j] - mean[j]),2) / 100.0;
//            }
//            stdv[j] = sqrt(stdv[j]);
//        }
//      return;
    }
    
    // TODO: Implement Otsu Bin or Histogram method. Don't know if this is the best implementation since we need to compute if a person is detected, then find how many people, then find where they are in separate steps. What if we could just scan the image for people and just get all three things at once??
    bool person_detected(){
        
        // mean temp method
        return curr_frame.mean_temp > background_temp + noise / 8.0;
        
    }
    
    // TODO: Update velocity directions given current and past frame
    void update_velocities();
    
    unsigned int count = 0;
    double background_temp;
    double noise;
    // Going to need array of detected people, probably dynamically allocated
    Frame curr_frame;
    Frame past_frame;
};


