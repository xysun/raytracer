#include "Sampler.h"

Sample::Sample(float _x, float _y){
    x = _x;
    y = _y;
}


Sampler::Sampler(int w, int h){
    width = w;
    height = h;
    pixels = w * h;
    current_pixel = 0;
}

bool Sampler::getSample(Sample *sample){
    
    if (current_pixel >= pixels){ // used up
        return false;
    }else{
        *sample = Sample(current_pixel % width + 0.5, current_pixel / width + 0.5);
        current_pixel += 1;
        return true;
    }
    
    
}