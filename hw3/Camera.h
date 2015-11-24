#pragma once

#include "Transform.h"

class Camera{
public:
    vec3 lookFrom = vec3();
    vec3 lookAt = vec3();
    vec3 up = vec3();
    float fovy;
    Camera(vec3, vec3, vec3, float);
};