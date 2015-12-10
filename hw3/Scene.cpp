#include "Scene.h"

bool Scene::intersect(Ray &ray, float *thit, Intersection *in){
    // go through every object in scene, return closest
    float _thit = INFINITY;
    LocalGeo _local = LocalGeo(Point(vec3(0,0,0)), Normal(vec3(0,0,0)));
    Shape *_shape = new Sphere();
    
    bool hit = false;
    
    for (int i = 0; i < num_objects; i++) {
        if (shapes[i]->intersect(ray, thit, in->localGeo)){
            if (*thit <= _thit) {
                _thit = *thit;
                _local = *(in->localGeo);
                _shape = shapes[i];
            }
            hit = true;
        }
    }
    
    *thit = _thit;
    *(in->localGeo) = _local;
    in->shape = _shape;
    
    return hit;
    
}

Color Scene::findColor(Intersection *in) {
    
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
            // point light = diffuse * light color * max (normal dot direction, 0);
            vec3 direction = glm::normalize(light->position - in->localGeo->point.p);
            vec3 normal = in->localGeo->normal.p;
            vec3 diffuse = vec3(in->shape->diffuse[0], in->shape->diffuse[1], in->shape->diffuse[2]);
            vec3 lightColor = vec3((int)light->color.r, (int)light->color.g, (int)light->color.b);
            
            float nDotL = glm::dot(normal, direction);
            float m = nDotL > 0? nDotL : 0;
            
            Color lambert = Color(diffuse.x * lightColor.x * m,
                                  diffuse.y * lightColor.y * m,
                                  diffuse.z * lightColor.z * m);
            
            // phong: for specular
            // myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess)
            vec3 eyepos = vec3(0,0,0);
            vec3 eyedirn = glm::normalize(eyepos - in->localGeo->point.p);
            vec3 halfvec = glm::normalize(eyedirn + direction);
            float nDotH = glm::dot(normal, halfvec);
            float n = nDotH > 0? nDotH : 0;
            float pn = powf(n, in->shape->shininess);
            vec3 specular = vec3(in->shape->specular[0], in->shape->specular[1], in->shape->specular[2]);
            
            
            Color phong = Color(specular.x * lightColor.x * pn,
                                specular.y * lightColor.y * pn,
                                specular.z * lightColor.z * pn);
            
            
            color.r += lambert.r + phong.r;
            color.g += lambert.g + phong.g;
            color.b += lambert.b + phong.b;
        }
    }
    
    return color;
}