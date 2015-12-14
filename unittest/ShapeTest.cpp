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

TEST(SphereTest, NotInCentralTest){
    Sphere sphere = Sphere(vec3(-2,0,0),1);
    Ray ray = Ray(vec3(0,0,3), vec3(-4,0,-1), 0, 0, 100);
    EXPECT_EQ(sphere.intersectP(ray), false);

}

TEST(SphereTest, TranslateIntersectTest){
    Sphere sphere = Sphere(vec3(2.0001,0,0), 1);
    sphere.set_transform(mat4(1,0,0,0,
                              0,1,0,0,
                              0,0,1,0,
                              -1,0,0,1)); //center now at (1.1,0,0)
    
    Ray ray = Ray(vec3(0,0,2), vec3(0,0,-1), 0, 0, 100);
    EXPECT_EQ(sphere.intersectP(ray), false);
}

TEST(SphereTest, TranslateIntersectNormalTest){
    Sphere sphere = Sphere(vec3(2,0,0), 1);
    sphere.set_transform(mat4(1,0,0,0,
                              0,1,0,0,
                              0,0,1,0,
                              -1,0,0,1)); //center now at (1,0,0)
    
    Ray ray = Ray(vec3(0,0,2), vec3(0,0,-1), 0, 0, 100);
    EXPECT_EQ(sphere.intersectP(ray), true);
    
    LocalGeo *local = new LocalGeo(Point(), Normal());
    float *t = new float(0);
    
    sphere.intersect(ray, t, local);
    EXPECT_EQ(local->normal.p, vec3(-1,0,0));
}

TEST(SphereTest, MaxMinTransformedTest){
    Sphere sphere = Sphere(vec3(2,0,0), 1);
    sphere.set_transform(mat4(1,0,0,0,
                              0,1,0,0,
                              0,0,1,0,
                              -1,0,0,1)); // center now at (1,0,0)
    sphere.set_max_min_transformed_xyz();
    
    EXPECT_EQ(sphere.max_transformed_x, 2);
    EXPECT_EQ(sphere.min_transformed_x, 0);
    EXPECT_EQ(sphere.max_transformed_y, 1);
    EXPECT_EQ(sphere.min_transformed_y, -1);
    EXPECT_EQ(sphere.max_transformed_z, 1);
    EXPECT_EQ(sphere.min_transformed_z, -1);
}


TEST(CubeTest, IntersectTest){
    Cube cube = Cube();
    cube.lowerLeftCorner = vec3(-1,-1,0);
    cube.size = 2;
    
    Ray ray = Ray(vec3(0,0,2), vec3(0,0,-1), 0, 0, 100);
    
    EXPECT_EQ(cube.intersectP(ray), true);
}

