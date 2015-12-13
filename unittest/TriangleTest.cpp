#include <gtest/gtest.h>
#include "Shape.h"
#include "variables.h"


TEST(TriangleTest, BaryCentricTest) {
    
    // (1,1,1) = 1/3 * (1,0,0) + 1/3 * (0,0,1) + 1/3 * (0,1,0)
    
    float x, y, z;
    
    Triangle tri = Triangle();
    tri.vert1 = vec3(1,0,0);
    tri.vert2 = vec3(0,0,1);
    tri.vert3 = vec3(0,1,0);
    
    tri.baryCentric(vec4(1,1,1,1),  x, y, z);
    
    EXPECT_FLOAT_EQ(x, 1.0f/3);
    EXPECT_FLOAT_EQ(y, 1.0f/3);
    EXPECT_FLOAT_EQ(z, 1.0f/3);
    
}

TEST(TriangleTest, IntersectTest){
    Triangle tri = Triangle();
    // counter clockwise
    tri.vert1 = vec3(1,0,0);
    tri.vert2 = vec3(0,1,0);
    tri.vert3 = vec3(0,0,0);
    
    Ray ray = Ray(vec4(0,0,2,1), vec4(0,0,-1,0), 0, 0, 100);
    EXPECT_EQ(tri.intersectP(ray), true);
    // t = 2
    float *t = new float(0);
    LocalGeo *local = new LocalGeo(Point(), Normal());
    
    tri.intersect(ray, t, local);
    
    EXPECT_EQ(*t, 2);
    EXPECT_EQ(local->point.p, vec4(0,0,0,1));
    
    
    Ray ray2 = Ray(vec4(0,-1,2,1), vec4(0,0,-1,0), 0, 0, 100);
    EXPECT_EQ(tri.intersectP(ray2), false);
}
