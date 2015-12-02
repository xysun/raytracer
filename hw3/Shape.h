#pragma once

#include "Ray.h"
#include "Transform.h"

class Point{
public:
    vec3 p = vec3(0,0,0);
    Point(vec3 _p)
    {p = _p;};
};

class Normal{
public:
    vec3 p = vec3(0,0,0);
    Normal(vec3 _p)
    {p = _p;};

};

class LocalGeo{
public:
    Point point = Point(vec3(0,0,0));
    Normal normal = Normal(vec3(0,0,0));
    LocalGeo(Point _p, Normal _n)
    {point = _p; normal = _n;};
};


class Shape{
public:
    float diffuse[3] = {0,0,0};
    virtual bool intersectP(Ray &ray) = 0;
    virtual bool intersect(Ray &ray, float *thit, LocalGeo *local) = 0;
    virtual ~Shape() {};
    
    void set_diffuse(float _diffuse[3]){
        diffuse[0] = _diffuse[0];
        diffuse[1] = _diffuse[1];
        diffuse[2] = _diffuse[2];
    }
};

class Sphere:public Shape{
    void get_quadratic_function(Ray &ray, float* a, float*b, float* c);
public:
    vec3 center;
    float radius;
    Sphere(vec3, float);
    ~Sphere(){};
    
    bool intersectP(Ray &ray);
    bool intersect(Ray &ray, float *thit, LocalGeo *local);
};