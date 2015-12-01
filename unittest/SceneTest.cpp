#include <gtest/gtest.h>
#include "Scene.h"
#include "readfile.h"


TEST(SceneTest, NoIntersectTest) {
    Scene *scene = new Scene(10,10);
    
    readfile("/Users/jsun/code/ucsd/hw3/unittest/SceneTest1.txt", scene);
    
    Ray ray = Ray(vec3(0,0,2), vec3(0,0,-1), 0, 0, 100);
    
    float *thit = new float(INFINITY);
    LocalGeo *local = new LocalGeo(Point(vec3(0,0,0)), Normal(vec3(0,0,0)));
    
    EXPECT_EQ(scene->intersect(ray, thit, local), false);
    
}

TEST(SceneTest, ClosestIntersectTest){
    Scene *scene = new Scene(10,10);
    
    readfile("/Users/jsun/code/ucsd/hw3/unittest/SceneTest2.txt", scene);
    
    Ray ray = Ray(vec3(0,0,2), vec3(0,0,-1), 0, 0, 100);
    
    float *thit = new float(INFINITY);
    LocalGeo *local = new LocalGeo(Point(vec3(0,0,0)), Normal(vec3(0,0,0)));
    
    EXPECT_EQ(scene->intersect(ray, thit, local), true);
    EXPECT_EQ(*thit, 1);
    EXPECT_EQ(local->point.p.z, 1);
    EXPECT_EQ(local->normal.p.z, 1);
    
    
}
