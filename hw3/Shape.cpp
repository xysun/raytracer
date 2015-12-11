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

vec3 Triangle::getNormal(){
    // A B C clockwise; C = vert1, B = vert2, A = vert3
    // n = (C-A)x(B-A)
    return glm::cross(vert1 - vert3, vert2 - vert3);
}


void Triangle::solveLinearEquation(vec3 left, vec3 right1, vec3 right2, float *x, float *y){
    /* 
     left = x*right1 + y*right2
     
     left.x = x * right1.x + y * right2.x
     left.y = x * right1.y + y * right2.y
     left.z = x * right1.z + y * right2.z
        
     left.x * right1.y = x * right1.x * right1.y + y * right2.x * right1.y
     left.y * right1.x = x * right1.x * right1.y + y * right1.x * right2.y
     
     left.x * right1.y - left.y * right1.x = y * (right2.x * right1.y - right1.x * right2.y)
     x = (left.x - y * right2.x) / right1.x
    */
    
    float _x, _y;
    
    if (right1.x == 0) {
        _y = left.x / right2.x;
        if (right1.y == 0) {
            _x = (left.z - _y * right2.z) / right1.z;
        }else{
            _x = (left.y - right2.y * _y) / right1.y;
        }
        
        *x = _x;
        *y = _y;
        return;
    }
    
    if (right2.x == 0) {
        _x = left.x / right1.x;
        if (right2.y == 0) {
            _y = (left.z - _x * right1.z) / right2.z;
        }else{
            _y = (left.y - _x * right1.y) / right2.y;
        }
        *x = _x;
        *y = _y;
        return;
    }
    
    
    _y = (left.x * right1.y - left.y * right1.x) / (right2.x * right1.y - right1.x * right2.y);
    _x = (left.x - _y * right2.x) / right1.x;
    
    *x = _x;
    *y = _y;
    
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
    vec3 normal = getNormal();
    float t = (glm::dot(vert3, normal) - glm::dot(ray.pos, normal)) / (glm::dot(ray.dir, normal));
    vec3 rayP = ray.pos + t * ray.dir;
    vec3 PminusA = rayP - vert3;
    vec3 BminusA = vert2 - vert3;
    vec3 CminusA = vert1 - vert3;
    
    // P - A = beta(B - A) + gamma(C - A)
    // 0 <= beta <= 1; 0 <= gamma <= 1; beta + gamma <= 1
    float *beta = new float(0);
    float *gamma = new float(0);
    solveLinearEquation(PminusA, BminusA, CminusA, beta, gamma);
    
    if (*beta >= 0 && *beta <= 1 && *gamma >= 0 && *gamma <= 1 && (*beta + *gamma) <= 1) {
        
        *thit = t;
        *local = LocalGeo(Point(rayP), Normal(normal));
        
        delete beta;
        delete gamma;
        
        return true;
    }else{
        delete beta;
        delete gamma;
        return false;
    }
}