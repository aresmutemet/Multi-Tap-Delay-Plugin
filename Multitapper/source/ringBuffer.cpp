//
//  ringBuffer.cpp
//  Multitapper
//
//  Created by Areş Mutemet on 15/04/2023.
//

#include "ringBuffer.h"

ringBuffer::ringBuffer(int size)
{
    // Create ring buffer(0 to size) Position at 0
    mBuffer = std::vector<double>(size, 0);
    mPos = 0;
}

double ringBuffer::read(int delay)
{
    delay = std::min(delay, (int)(mBuffer.size() - 1));
    int index = mPos - delay;
    if (index < 0)index += mBuffer.size();
    return mBuffer[index];
}

double ringBuffer::interpolation(double delay)
{
    // Read two samples and interpolate between them
    int samples = int(delay);
    double v1 = read(samples);
    double v2 = read(samples + 1);
    double frac = delay - samples;
    return v1 + frac * (v2 - v1);
}

void ringBuffer::write(double val)
{
    // Write the sample current position
    mBuffer[mPos] = val;
    mPos = (mPos + 1) % mBuffer.size();
}
