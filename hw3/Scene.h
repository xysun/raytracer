#pragma once

#include "Color.h"
#include "Camera.h"
#include "Shape.h"

class Scene{
public:
    int w,h;
    Shape** shapes;
    
    Camera* camera = new Camera(vec3(),vec3(),vec3(),0);
    
    Scene(int _w, int _h)
    {w = _w; h = _h; shapes = new Shape*[10];};
    
};