#include <gtest/gtest.h>
#include "Camera.h"


TEST(CameraTest, PassValuesToVec3) {
    Camera c = Camera(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0), 90);
    EXPECT_EQ(c.lookFrom.z, 2);
    EXPECT_EQ(c.lookAt.y, 0);
    EXPECT_EQ(c.up.y, 1);
    EXPECT_EQ(c.fovy, 90);
    
    // coord frame
    EXPECT_EQ(c.u, vec3(1,0,0));
    EXPECT_EQ(c.v, vec3(0,1,0));
    EXPECT_EQ(c.w, vec3(0,0,1));
}

TEST(CameraTest, GenerateRay){
    Camera c = Camera(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0), 90);
    
    
    
}