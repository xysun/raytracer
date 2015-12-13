#include <gtest/gtest.h>
#include "Shape.h"
#include "variables.h"


TEST(IntersectTest, IntersectPTest) {

    Sphere sphere = Sphere(vec3(1,0,0), 1);
    
    Ray ray = Ray(vec3(-1,0,0), vec3(0,1,0), 0, 0, 100);
    EXPECT_FALSE(sphere.intersectP(ray));
    
    Ray ray2 = Ray(vec3(0,0,0), vec3(0,1,0), 0, 0, 100);
    EXPECT_TRUE(sphere.intersectP(ray2));

}

TEST(IntersectTest, IntersectValueTest){
 
    Sphere sphere = Sphere(vec3(1,0,0), 1);
    
    float *thit = new float(0);
    LocalGeo *local = new LocalGeo(Point(vec4(0,0,0,1)), Normal(vec3(0,0,0)));

    // 2 real positive roots, pick smaller one
    Ray ray1 = Ray(vec3(-1,0,0), vec3(1,0,0), 0, 0, 100);
    sphere.intersect(ray1, thit, local);
    EXPECT_EQ(*thit, 1);
    EXPECT_EQ(local->point.p, vec4(0,0,0,1));
    EXPECT_EQ(local->normal.p, vec3(-1,0,0));
    
    // tangent
    Ray ray2 = Ray(vec3(0,0,0), vec3(0,1,0), 0, 0, 100);
    EXPECT_EQ(sphere.intersect(ray2, thit, local), true);
    EXPECT_EQ(*thit, 0);
    EXPECT_EQ(local->point.p, vec4(0,0,0,1));
    EXPECT_EQ(local->normal.p, vec3(-1,0,0));
    
    // one positive, one negative
    Ray ray3 = Ray(vec3(1,0,0), vec3(1,0,0), 0, 0, 100);
    EXPECT_EQ(sphere.intersect(ray3, thit, local), true);
    EXPECT_EQ(*thit, 1);
    EXPECT_EQ(local->point.p, vec4(2,0,0,1));
    EXPECT_EQ(local->normal.p, vec3(1,0,0));
    
    // no intersection
    Ray ray4 = Ray(vec3(-1,0,0), vec3(0,1,0), 0, 0, 100);
    EXPECT_EQ(sphere.intersect(ray4, thit, local), false);
    
    
    
}

