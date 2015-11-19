#include "Film.h"
#include <FreeImage.h>

#include <stdio.h>


Film::Film(int _w, int _h){
    w = _w;
    h = _h;
}

void Film::writeImage(){
    FreeImage_Initialise();
    
    FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
    
    char fname[] = "output";
    
    FreeImage_Save(FIF_PNG, img, fname, 0);
    
    FreeImage_DeInitialise();
}

void Film::commit(Sample &sample, Color &color){
    // assign color to pixels
    int x = (int) (sample.x - 0.5);
    int y = (int) (sample.y - 0.5);
    
    int i = y * w + x;
    
    int j = i * w; // starting element
    
    //printf("x: %d, y: %d, i: %d, j:%d\n", x, y, i, j);
    
    pixels[j] = color.r;
    pixels[j+1] = color.g;
    pixels[j+2] = color.b;
}

unsigned char Film::getPixel(int i){
    return pixels[i];
}