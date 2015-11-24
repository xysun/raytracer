#include "Transform.h"

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
    vec3 x = glm::cross(up,zvec);
    vec3 y = glm::cross(zvec,x);
    vec3 ret = glm::normalize(y);
    return ret;
}


Transform::Transform()
{
    
}

Transform::~Transform()
{
    
}