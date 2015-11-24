#include <gtest/gtest.h>
#include "Transform.h"


TEST(TransformTest, UpVector) {
    vec3 zvec = vec3(0,0,2);
    vec3 up = vec3(0,3,0);
    
    vec3 upVector = Transform::upvector(up, zvec);
    
    EXPECT_EQ(upVector, vec3(0,1,0));
}
