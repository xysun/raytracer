#pragma once

#include "Color.h"
#include "Camera.h"
#include "Shape.h"
#include "variables.h"

class Scene{
public:
    int w,h;
    int num_objects = 0;
    Shape** shapes;
    
    Camera* camera = new Camera(vec3(),vec3(),vec3(),0);
    
    Scene(int _w, int _h)
    {w = _w; h = _h; shapes = new Shape*[max_objects];};
    
};