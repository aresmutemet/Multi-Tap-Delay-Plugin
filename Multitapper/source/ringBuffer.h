//
//  ringBuffer.hpp
//  Multitapper
//
//  Created by Areş Mutemet on 15/04/2023.
//

#pragma once
#include <vector>

class ringBuffer {
public:
    
    ringBuffer(int size);
    
    // Read Function
    double read(int delay);
    
    // Write Function
    void write(double val);
    
    //Interpolation Function
    double interpolation(double delay);
   
private:
    
    //mBuffer storing the samples
    std::vector<double> mBuffer;
    
    // Position
    int mPos;
};
