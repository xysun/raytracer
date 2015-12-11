#include <gtest/gtest.h>
#include "Shape.h"


TEST(TriangleTest, SolveLinearEquation) {
    
    // (1,0,1) = 1 * (1,0,0) + 1 * (0,0,1)
    vec3 left = vec3(1,0,1);
    vec3 right1 = vec3(1,0,0);
    vec3 right2 = vec3(0,0,1);
    
    float *x = new float(0);
    float *y = new float(0);
    
    Triangle tri = Triangle();
    
    tri.solveLinearEquation(left, right1, right2, x, y);
    
    EXPECT_EQ(*x, 1);
    EXPECT_EQ(*y, 1);
    
    delete x;
    delete y;
    
    
}
