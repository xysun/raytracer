#pragma once

#include <glm/glm.hpp>

typedef glm::vec3 vec3 ;
const float pi = 3.14159265 ;

class Transform
{
public:
    Transform();
    virtual ~Transform();
    static vec3 upvector(const vec3 &up, const vec3 &zvec) ;
};