#pragma once
#include "Color.h"
#include <string>


class Light{
public:
    std::string name;
    virtual ~Light(){};
};

class AmbientLight:public Light{
public:
    std::string name = "ambient";
    Color color = Color(0,0,0);
    
    AmbientLight(Color _color){
        color = _color;
    }
    
    ~AmbientLight(){};
    
};