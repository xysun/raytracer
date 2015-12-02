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

Color Scene::findColor(LocalGeo *local) {
    
    Color color = Color(0, 0, 0);
    
    for (int i = 0; i < num_lights; i++) {
        
        if (dynamic_cast<AmbientLight*>(lights[i]) != 0) {
            AmbientLight* light = dynamic_cast<AmbientLight*>(lights[i]);
            color.r += light->color.r;
            color.g += light->color.g;
            color.b += light->color.b;
        }
        
        if (dynamic_cast<PointLight*>(lights[i]) != 0) {
            PointLight* light = dynamic_cast<PointLight*>(lights[i]);
            
        }
    }
    
    return color;
}