#pragma once

#include "Transform.h"

class Camera{
public:
    vec3 lookFrom = vec3();
    vec3 lookAt = vec3();
    vec3 up = vec3();
    float fovy;
    Camera(vec3 _lookFrom, vec3 _lookAt, vec3 _up, float _fovy){
        lookFrom = _lookFrom;
        lookAt = _lookAt;
        up = _up;
        fovy = _fovy;
    };
};