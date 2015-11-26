#pragma once

#include "Ray.h"
#include "Transform.h"

class Point{
public:
    float x,y,z;
    Point(float _x, float _y, float _z)
    {x = _x; y = _y; z = _z;};
};

class Normal{
public:
    float x,y,z;
    Normal(float _x, float _y, float _z)
    {x = _x; y = _y; z = _z;};
    
};

class LocalGeo{
public:
    Point point = Point(0,0,0);
    Normal normal = Normal(0,0,0);
    LocalGeo(Point _p, Normal _n)
    {point = _p; normal = _n;};
};


class Shape{
public:
    virtual bool intersectP(Ray &ray) = 0;
    virtual bool intersect(Ray &ray, float *thit, LocalGeo *local) = 0;
};

class Sphere:public Shape{
public:
    vec3 center;
    float radius;
    Sphere(vec3, float);
    bool intersectP(Ray &ray);
    bool intersect(Ray &ray, float *thit, LocalGeo *local);
};