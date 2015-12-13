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
    // vertices
    int max_vertices = 0;
    vec3 vertices[100000];
    int current_vertex = 0;
    int maxdepth = 0;
    
    
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
    bool intersectP(Ray &ray, Shape *shape);
    
    Color findColor(Intersection *in);
    
    void rayTrace(Ray &ray, int depth, Color *color);
    
    static Ray createReflectedRay(LocalGeo local, Ray ray);
    
    Color computePointLight(vec3 direction,
                            vec3 lightColor,
                            vec3 normal,
                            vec3 halfvec,
                            Shape* shape);
    
};