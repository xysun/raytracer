#include <gtest/gtest.h>
#include "Camera.h"


TEST(ReadFileTest, PassValuesToVec3) {
    Camera c = Camera(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), 1);
    EXPECT_EQ(c.lookFrom.x, 1);
    EXPECT_EQ(c.lookAt.y, 1);
    EXPECT_EQ(c.up.z, 1);
}