#include "Sampler.h"
#include <stdio.h>

Sample::Sample(float _x, float _y){
    x = _x;
    y = _y;
}


Sampler::Sampler(int _w, int _h){
    width = _w;
    height = _h;
    current_pixel = 0;
    pixels = _w * _h;
}

bool Sampler::getSample(Sample *sample){
    
    if (current_pixel >= pixels){ // used up
        return false;
    }else{
        *sample = Sample(current_pixel % width + 0.5, current_pixel / width + 0.5);
        current_pixel += 1;
        //printf("current pixel after assigning sample: %d\n", current_pixel);
        return true;
    }
    
    
}