#pragma once

class Color{
public:
    unsigned char r,g,b;
    Color(int _r, int _g, int _b){
        r = (unsigned char) _r;
        g = (unsigned char) _g;
        b = (unsigned char) _b;
    };
    
    void clamp(){
        r = r > 255? 255:r;
        g = g > 255? 255:g;
        b = b > 255? 255:b;
    }
};