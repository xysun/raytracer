#include "Shape.h"

Sphere::Sphere(vec3 _center, float _radius){
    center = _center;
    radius = _radius;
}


void Sphere::get_quadratic_function(Ray &ray, float *a, float *b, float *c){
    vec3 p0 = ray.pos;
    vec3 p1 = ray.dir;
    
    // p1 * p1
    *a = glm::dot(p1, p1);
    // 2p1*(p0-c)
    *b = 2 * (glm::dot(p1, p0 - center));
    // (p0-c)*(p0-c)-r^2
    *c = glm::dot(p0-center, p0-center) - radius * radius;
    
}

bool Sphere::intersectP(Ray &ray){
    
    float * _a = new float(0);
    float * _b = new float(0);
    float * _c = new float(0);
    
    get_quadratic_function(ray, _a, _b, _c);
    
    float delta = (*_b) * (*_b) - 4*(*_a)*(*_c);
    
    if (delta >=0 ) {
        return true;
    }else{
        return false;
    }
}

bool Sphere::intersect(Ray &ray, float *thit, LocalGeo *local){
    
    float * _a = new float(0);
    float * _b = new float(0);
    float * _c = new float(0);
        
    get_quadratic_function(ray, _a, _b, _c);
        
    float a = *_a;
    float b = *_b;
    float c = *_c;
        
    float delta = b*b - 4*a*c;
        
    if (delta >= 0){
        
        if (delta == 0) {
            // tangent
            *thit = -b / (2*a);
        }
        else{
            float square_delta = sqrtf(delta);
            float root1 = (-b + square_delta) / (2*a);
            float root2 = (-b - square_delta) / (2*a);
            
            if (root1 > 0 && root2 > 0){
                // 2 positive root, pick smaller
                *thit = fmin(root1, root2);
            }else if (root1 > 0 && root2 < 0){
                *thit = root1;
            }else if (root1 <0 && root2 >0){
                *thit = root2;
            }else{ // TODO: ==0?
                return false;
            }
        }
        
        vec3 point = ray.pos + ray.dir * (*thit);
        vec3 normal = glm::normalize(point - center);
        *local = LocalGeo(Point(point), Normal(normal));
        
        return true;
    }
    else{
        return false;
    }
}