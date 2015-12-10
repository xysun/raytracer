#pragma once

#include "Color.h"
#include "Camera.h"
#include "Shape.h"
#include "variables.h"
#include "Light.h"

class Scene{
public:
    int w,h;
    int num_objects = 0;
    int num_lights = 0;
    Shape** shapes;
    Light** lights;
    
    Camera* camera = new Camera(vec3(),vec3(),vec3(),0);
    
    Scene(int _w, int _h)
    {
        w = _w;
        h = _h;
        shapes = new Shape*[max_objects];
        lights = new Light*[max_lights];
    };
    
    bool intersect(Ray &ray, float *thit, Intersection *in);
    
    Color findColor(Intersection *in);
    
    Color computePointLight(vec3 direction,
                            vec3 lightColor,
                            vec3 normal,
                            vec3 halfvec,
                            Shape* shape);
    
};