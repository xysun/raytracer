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
