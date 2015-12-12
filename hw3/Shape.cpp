#include "Shape.h"
#include <stdio.h>

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

void Triangle::setNormal(){
    // A B C clockwise; C = vert1, B = vert2, A = vert3
    // n = (C-A)x(B-A)
    normal = glm::cross(vert1 - vert3, vert2 - vert3);
    
}

void Triangle::baryCentric(vec3 p, float &alpha, float &beta, float &gamma){
    
    // u = alpha, v = beta, w = gamma
    
    vec3 v0 = vert2 - vert1;
    vec3 v1 = vert3 - vert1;
    vec3 v2 = p - vert1;
    
    float d00 = glm::dot(v0, v0);
    float d01 = glm::dot(v0, v1);
    float d11 = glm::dot(v1, v1);
    float d20 = glm::dot(v2, v0);
    float d21 = glm::dot(v2, v1);
    
    float denom = d00 * d11 - d01 * d01;
    beta = (d11 * d20 - d01 * d21) / denom;
    gamma = (d00 * d21 - d01 * d20) / denom;
    alpha = 1.0f - beta - gamma;
    
    
}


bool Triangle::intersectP(Ray &ray){
    
    float *t = new float(0);
    LocalGeo *local = new LocalGeo(Point(), Normal());
    
    bool res = intersect(ray, t, local);
    
    delete t;
    delete local;
    
    return res;
}

bool Triangle::intersect(Ray &ray, float *thit, LocalGeo *local){
    
    // A B C clockwise: C = vert1, B = vert2, A = vert3
    // t = (A dot n - Ray.pos dot n) / (Ray.dir dot n)
    setNormal();
    float t = (glm::dot(vert3, normal) - glm::dot(ray.pos, normal)) / (glm::dot(ray.dir, normal));
    vec3 rayP = ray.pos + t * ray.dir;
    
    // 0 <= beta <= 1; 0 <= gamma <= 1; beta + gamma <= 1
    float alpha, beta, gamma;
    baryCentric(rayP, alpha, beta, gamma);
    
    if (beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1 && (beta + gamma) <= 1) {
        
        *thit = t;
        *local = LocalGeo(Point(rayP), Normal(normal));
        
        return true;
    }else{
        return false;
    }
}