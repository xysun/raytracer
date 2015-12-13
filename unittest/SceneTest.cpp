#include <gtest/gtest.h>
#include "Scene.h"
#include "readfile.h"
#include "variables.h"


TEST(SceneTest, NoIntersectTest) {
    Scene *scene = new Scene(10,10);
    
    readfile("/Users/jsun/code/ucsd/hw3/unittest/SceneTest1.txt", scene);
    
    Ray ray = Ray(vec4(0,0,2,1), vec4(0,0,-1,0), 0, 0, 100);
    
    float *thit = new float(INFINITY);
    Intersection *in = new Intersection();
    
    EXPECT_EQ(scene->intersect(ray, thit, in), false);
    
    delete thit;
    delete in;
    
}

TEST(SceneTest, ClosestIntersectTest){
    Scene *scene = new Scene(10,10);
    
    readfile("/Users/jsun/code/ucsd/hw3/unittest/SceneTest2.txt", scene);
    
    Ray ray = Ray(vec4(0,0,2,1), vec4(0,0,-1,0), 0, 0, 100);
    
    float *thit = new float(INFINITY);
    Intersection *in = new Intersection();
    
    EXPECT_EQ(scene->intersect(ray, thit, in), true);
    EXPECT_EQ(*thit, 1);
    EXPECT_EQ(in->localGeo->point.p.z, 1);
    EXPECT_EQ(in->localGeo->normal.p.z, 1);
    
    
    Sphere* sphere = dynamic_cast<Sphere*>(in->shape);
    EXPECT_EQ(sphere->center.z, 0);
    EXPECT_EQ(sphere->center.x, 0);
    EXPECT_EQ(sphere->center.y, 0);
    
    
    delete thit;
    delete in;
    
    
}

TEST(SceneTest, ShadowTest){
    
    Scene *scene = new Scene(10,10);
    
    readfile("/Users/jsun/code/ucsd/hw3/unittest/SceneTest3.txt", scene);

    // ray1: myposn = (2,0,0), shadow
    Ray shadowRay1 = Ray(vec3(2,0,0), vec3(-4,0,0) - vec3(2,0,0), 1, 1, 100);
    EXPECT_EQ(scene->intersectP(shadowRay1, scene->shapes[1]), true);
    
    // ray2: myposn = (4,2,0), no shadow
    Ray shadowRay2 = Ray(vec3(4,2,0), vec3(-4,0,0) - vec3(4,2,0), 1, 1, 100);
    EXPECT_EQ(scene->intersectP(shadowRay2, scene->shapes[1]), false);
    
    // first sphere should never be in shadow
    Ray shadowRay3 = Ray(vec3(-1,0,0), vec3(-4,0,0) - vec3(-1,0,0),0,0,100);
    EXPECT_EQ(scene->intersectP(shadowRay3, scene->shapes[0]), false);
    
}

TEST(SceneTest, ReflectedRayTest){
    
    LocalGeo local = LocalGeo(Point(vec4(0,0,0,1)), Normal(vec3(0,1,0)));
    Ray ray1 = Ray(vec3(-1,1,0), vec3(0,0,0) - vec3(-1,1,0), 0, 0, 100);
    
    Ray reflectedRay = Scene::createReflectedRay(local, ray1);
    EXPECT_EQ(reflectedRay.pos, vec4(0,0,0,1));
    EXPECT_EQ(reflectedRay.dir, glm::normalize(vec4(1,1,0,0)));
}
