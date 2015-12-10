#pragma once

#include "Ray.h"
#include "Transform.h"

class Point{
public:
    vec3 p = vec3(0,0,0);
    Point(vec3 _p)
    {p = _p;};
    Point(){};
};

class Normal{
public:
    vec3 p = vec3(0,0,0);
    Normal(vec3 _p)
    {p = _p;};
    Normal(){};

};

class LocalGeo{
public:
    Point point = Point();
    Normal normal = Normal();
    LocalGeo(Point _p, Normal _n)
    {point = _p; normal = _n;};
};


class Shape{
public:
    float diffuse[3] = {0,0,0};
    float shininess = 0;
    virtual bool intersectP(Ray &ray) = 0;
    virtual bool intersect(Ray &ray, float *thit, LocalGeo *local) = 0;
    virtual ~Shape() {};
    
    void set_diffuse(float _diffuse[3]){
        diffuse[0] = _diffuse[0];
        diffuse[1] = _diffuse[1];
        diffuse[2] = _diffuse[2];
    }
    
    void set_shininess(float _s){
        shininess = _s;
    }
};


class Sphere:public Shape{
    void get_quadratic_function(Ray &ray, float* a, float*b, float* c);
public:
    vec3 center;
    float radius;
    Sphere(vec3, float);
    Sphere(){
        center = vec3(0,0,0);
        radius = 0;
    }
    ~Sphere(){};
    
    bool intersectP(Ray &ray);
    bool intersect(Ray &ray, float *thit, LocalGeo *local);
};


class Intersection{
public:
    LocalGeo *localGeo = new LocalGeo(Point(), Normal());
    Shape * shape = new Sphere();
    Intersection(){};
};


