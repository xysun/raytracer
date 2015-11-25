#pragma once
#include "Transform.h"

class Ray{
public:
    vec3 pos = vec3(0,0,0);
    vec3 dir = vec3(0,0,0);
    float t = 0.0;
    float t_min = 0.0;
    float t_max = 0.0;
    
    Ray(vec3 _pos, vec3 _dir, float _t, float _t_min, float _t_max)
    {
        pos = _pos;
        dir = _dir;
        t = _t;
        t_min = _t_min;
        t_max = _t_max;
    }
};