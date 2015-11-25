#include "Shape.h"

Sphere::Sphere(vec3 _center, float _radius){
    center = _center;
    radius = _radius;
}

bool Sphere::intersectP(Ray &ray){
    
    return false;
}

bool Sphere::intersect(Ray &ray, float *thit, LocalGeo *local){
    
    return false;
}