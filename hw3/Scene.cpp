#include "Scene.h"

bool Scene::intersect(Ray &ray, float *thit, LocalGeo *local){
    // go through every object in scene, return closest
    float _thit = INFINITY;
    LocalGeo _local = LocalGeo(Point(vec3(0,0,0)), Normal(vec3(0,0,0)));
    bool hit = false;
    
    for (int i = 0; i < num_objects; i++) {
        if (shapes[i]->intersect(ray, thit, local)){
            if (*thit <= _thit) {
                _thit = *thit;
                _local = *local;
            }
            hit = true;
        }
    }
    
    *thit = _thit;
    *local = _local;
    
    return hit;
    
}