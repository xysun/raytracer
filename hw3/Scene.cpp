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

Color Scene::computePointLight(vec3 direction,
                               vec3 lightColor,
                               vec3 normal,
                               vec3 halfvec,
                               Shape* shape){
    
    // lambert: diffuse * light color * max (normal dot direction, 0);
    float nDotL = glm::dot(normal, direction);
    float m = nDotL > 0? nDotL:0;
    
    vec3 diffuse = vec3(shape->diffuse[0], shape->diffuse[1], shape->diffuse[2]);
    vec3 specular = vec3(shape->specular[0], shape->specular[1], shape->specular[2]);
    
    Color lambert = Color(diffuse.x * lightColor.x * m,
                          diffuse.y * lightColor.y * m,
                          diffuse.z * lightColor.z * m);
    
    // phong: myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess)
    float nDotH = glm::dot(normal, halfvec);
    float n = nDotH > 0? nDotH : 0;
    float pn = powf(n, shape->shininess);
    
    Color phong = Color(specular.x * lightColor.x * pn,
                        specular.y * lightColor.y * pn,
                        specular.z * lightColor.z * pn);
    
    if (pn > 0.01) {
        printf("normal: %.f %.f %.f\n", normal.x, normal.y, normal.z);
        printf("halfvec: %.f %.f %.f\n", halfvec.x, halfvec.y, halfvec.z);
        printf("nDotH: %.3f", nDotH);
        printf("pn: %.3f", pn);
        printf("phong: %d %d %d\n", phong.r, phong.g, phong.b);
    }
    
    return Color(lambert.r + phong.r,
                 lambert.g + phong.g,
                 lambert.b + phong.b);
    
    
}

Color Scene::findColor(Intersection *in) {
    
    Color color = Color(0, 0, 0);
    
    vec3 eyepos = vec3(0,0,0);
    vec3 eyedirn = glm::normalize(eyepos - in->localGeo->point.p);
    vec3 normal = in->localGeo->normal.p;
    
    
    for (int i = 0; i < num_lights; i++) {
        
        if (dynamic_cast<AmbientLight*>(lights[i]) != 0) {
            AmbientLight* light = dynamic_cast<AmbientLight*>(lights[i]);
            color.r += light->color.r;
            color.g += light->color.g;
            color.b += light->color.b;
        }
        
        if (dynamic_cast<PointLight*>(lights[i]) != 0) {
            PointLight* light = dynamic_cast<PointLight*>(lights[i]);
            vec3 direction = glm::normalize(light->position - in->localGeo->point.p);
            vec3 lightColor = vec3(light->color.r, light->color.g, light->color.b);
            vec3 halfvec = glm::normalize(eyedirn + direction);
            
            Color pointColor = computePointLight(direction,
                                               lightColor,
                                               normal,
                                               halfvec,
                                               in->shape);
            
            color.r += pointColor.r;
            color.g += pointColor.g;
            color.b += pointColor.b;
        }
        
        if (dynamic_cast<DirectionalLight*>(lights[i]) != 0) {
            DirectionalLight* light = dynamic_cast<DirectionalLight*>(lights[i]);
            vec3 direction = glm::normalize(light->position);
            vec3 lightColor =vec3(light->color.r, light->color.g, light->color.b);
            vec3 halfvec = glm::normalize(eyedirn + direction);
            
            Color directionalColor = computePointLight(direction, lightColor, normal, halfvec, in->shape);
            
            color.r += directionalColor.r;
            color.g += directionalColor.g;
            color.b += directionalColor.b;
            
        }
        
    }
    
    return color;
}