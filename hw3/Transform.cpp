#include "Transform.h"

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec)
{
    vec3 x = glm::cross(up,zvec);
    vec3 y = glm::cross(zvec,x);
    vec3 ret = glm::normalize(y);
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz)
{
    mat4 ret =  mat4(sx,0,0,0,
                     0,sy,0,0,
                     0,0,sz,0,
                     0,0,0,1);
    
    return ret;
    
}



Transform::Transform()
{
    
}

Transform::~Transform()
{
    
}