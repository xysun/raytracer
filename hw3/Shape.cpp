#include "Shape.h"
#include <stdio.h>
#include "variables.h"

Sphere::Sphere(vec3 _center, float _radius){
    center = _center;
    radius = _radius;
}


void Sphere::getQuadraticFunction(Ray &ray, float &a, float &b, float &c){
    vec4 p0 = ray.pos;
    vec4 p1 = ray.dir;
    
    // p1 * p1
    a = glm::dot(p1, p1);
    // 2p1*(p0-c)
    b = 2 * (glm::dot(p1, p0 - vec4(center,1)));
    // (p0-c)*(p0-c)-r^2
    c = glm::dot(p0-vec4(center,1), p0-vec4(center,1)) - radius * radius;
    
}

bool Sphere::intersectP(Ray &ray){
    
    float _a, _b, _c;
    
    getQuadraticFunction(ray, _a, _b, _c);
    
    float delta = (_b) * (_b) - 4*(_a)*(_c);
    
    if (delta >=0 ) {
        return true;
    }else{
        return false;
    }
}

bool Sphere::intersect(Ray &ray, float *thit, LocalGeo *local){
    
    float a,b,c;
        
    getQuadraticFunction(ray, a, b, c);
        
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
        
        vec4 point = ray.pos + ray.dir * (*thit);
        vec4 normal = glm::normalize(point - vec4(center,1));
        *local = LocalGeo(Point(point), Normal(vec3(normal.x, normal.y, normal.z)));
        
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

void Triangle::baryCentric(vec4 p, float &alpha, float &beta, float &gamma){
    
    // u = alpha, v = beta, w = gamma
    
    vec4 v0 = vec4(vert2,1) - vec4(vert1,1);
    vec4 v1 = vec4(vert3,1) - vec4(vert1,1);
    vec4 v2 = p - vec4(vert1,1);
    
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
    float t = (glm::dot(vec4(vert3,1), vec4(normal,1)) - glm::dot(ray.pos, vec4(normal,1))) / (glm::dot(ray.dir, vec4(normal,1)));
    vec4 rayP = ray.pos + t * ray.dir;
    
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