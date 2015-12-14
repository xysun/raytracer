#include "Shape.h"
#include <stdio.h>
#include "variables.h"
#include <algorithm>

Sphere::Sphere(vec3 _center, float _radius){
    center = _center;
    radius = _radius;
}


void Sphere::set_max_min_transformed_xyz(){
    vec4 transformed_center = transform * vec4(center, 1);
    max_transformed_x = transformed_center.x + radius;
    min_transformed_x = transformed_center.x - radius;
    max_transformed_y = transformed_center.y + radius;
    min_transformed_y = transformed_center.y - radius;
    max_transformed_z = transformed_center.z + radius;
    min_transformed_z = transformed_center.z - radius;
}

void Sphere::getQuadraticFunction(Ray &ray, float &a, float &b, float &c){
    vec3 p0 = vec3(ray.pos.x, ray.pos.y, ray.pos.z);
    vec3 p1 = vec3(ray.dir.x, ray.dir.y, ray.dir.z);
    
    // p1 * p1
    a = glm::dot(p1, p1);
    // 2p1*(p0-c)
    b = 2 * (glm::dot(p1, p0 - center));
    // (p0-c)*(p0-c)-r^2
    c = glm::dot(p0-center, p0-center) - radius * radius;
    
}

bool Sphere::intersectP(Ray &ray){
    
    float *t = new float(0);
    LocalGeo *local = new LocalGeo(Point(),Normal());
    
    bool res = Sphere::intersect(ray, t, local);
    
    delete t;
    delete local;
    
    return res;
}

bool Sphere::intersect(Ray &ray, float *thit, LocalGeo *local){
    
    // apply M-1 to ray
    mat4 invTransform = glm::inverse(transform);
    Ray rayTransformed = Ray(invTransform * ray.pos, invTransform*ray.dir, ray.t, ray.t_min, ray.t_max);
    
    float a,b,c;
        
    getQuadraticFunction(rayTransformed, a, b, c);
        
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
        
        vec4 point = rayTransformed.pos + rayTransformed.dir * (*thit);
        vec4 normal = glm::normalize(point - vec4(center,1));
        *local = LocalGeo(Point(point), Normal(vec3(normal.x, normal.y, normal.z)));
        
        return true;
    }
    else{
        return false;
    }
}

void Triangle::set_max_min_transformed_xyz(){
    
    vec4 transformed_v1 = transform * vec4(vert1,1);
    vec4 transformed_v2 = transform * vec4(vert2,1);
    vec4 transformed_v3 = transform * vec4(vert3,1);
    
    min_transformed_x = std::min(std::min(transformed_v1.x, transformed_v2.x), transformed_v3.x);
    max_transformed_x = std::max(std::max(transformed_v1.x, transformed_v2.x), transformed_v3.x);
    min_transformed_y = std::min(std::min(transformed_v1.y, transformed_v2.y), transformed_v3.y);
    max_transformed_y = std::max(std::max(transformed_v1.y, transformed_v2.y), transformed_v3.y);
    min_transformed_z = std::min(std::min(transformed_v1.z, transformed_v2.z), transformed_v3.z);
    max_transformed_z = std::max(std::max(transformed_v1.z, transformed_v2.z), transformed_v3.z);


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
    
    mat4 invTransform = glm::inverse(transform);

    Ray rayTransformed = Ray(invTransform * ray.pos, invTransform*ray.dir, ray.t, ray.t_min, ray.t_max);
    
    // A B C clockwise: C = vert1, B = vert2, A = vert3
    // t = (A dot n - Ray.pos dot n) / (Ray.dir dot n)
    setNormal();
    float t = (glm::dot(vec4(vert3,1), vec4(normal,1)) - glm::dot(rayTransformed.pos, vec4(normal,1))) / (glm::dot(rayTransformed.dir, vec4(normal,0)));

    vec4 rayP = rayTransformed.pos + t * rayTransformed.dir;
    
    // 0 <= beta <= 1; 0 <= gamma <= 1; beta + gamma <= 1
    float alpha, beta, gamma;
    baryCentric(rayP, alpha, beta, gamma);
    
    if (beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1 && (beta + gamma) <= 1) {
        
        *thit = t;
        *local = LocalGeo(Point(rayP), Normal(normal));
        
        // thit must > 0
        if (t > 0) {
            return true;
        }else{
            return false;
        }
        
    }else{
        return false;
    }
}

bool Cube::intersectP(Ray &ray){
    
    // no need to apply transform to ray
    
    vec3 v1 = lowerLeftCorner;
    vec3 v2 = vec3(v1.x, v1.y + size, v1.z);
    vec3 v3 = vec3(v1.x + size, v1.y + size, v1.z);
    vec3 v4 = vec3(v1.x + size, v1.y, v1.z);
    
    Triangle tri1 = Triangle(v4, v2, v1);
    Triangle tri2 = Triangle(v4,v3,v2);
    
    return tri1.intersectP(ray) || tri2.intersectP(ray);
    
}

void Cube::set_max_min_transformed_xyz(){
    // no transformation for cube
    min_transformed_x = lowerLeftCorner.x;
    min_transformed_y = lowerLeftCorner.y;
    min_transformed_z = lowerLeftCorner.z - size;
    
    max_transformed_x = lowerLeftCorner.x + size;
    max_transformed_y = lowerLeftCorner.y + size;
    max_transformed_z = lowerLeftCorner.z;
    
}

