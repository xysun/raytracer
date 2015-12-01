#pragma once
#include "Color.h"


class Light{
public:
    virtual ~Light(){};
};

class AmbientLight:public Light{
public:
    Color color = Color(0,0,0);
    
    AmbientLight(Color _color){
        color = _color;
    }
    
    ~AmbientLight(){};
    
};