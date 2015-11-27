#include <gtest/gtest.h>
#include "Shape.h"


TEST(IntersectTest, SphereNoIntersect) {

    Sphere sphere = Sphere(vec3(1,0,0), 1);
    
    Ray ray = Ray(vec3(-1,0,0), vec3(0,1,0), 0, 0, 100);
    EXPECT_FALSE(sphere.intersectP(ray));
    
    Ray ray2 = Ray(vec3(0,0,0), vec3(0,1,0), 0, 0, 100);
    EXPECT_TRUE(sphere.intersectP(ray2));

}

