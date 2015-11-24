#include <gtest/gtest.h>
#include "readfile.h"


TEST(ReadFileTest, ReadCorrectValues) {

    Scene *scene = new Scene(10,10);
    
    readfile("/Users/jsun/code/ucsd/hw3/unittest/readfile.txt", scene);
    
    EXPECT_EQ(scene->w, 100);
    EXPECT_EQ(scene->h, 100);
    
    EXPECT_EQ(scene->camera->up, vec3(0,1,0));
    EXPECT_EQ(scene->camera->lookFrom, vec3(0,0,2));
    EXPECT_EQ(scene->camera->lookAt, vec3(0,0,0));
    EXPECT_EQ(scene->camera->fovy, 90);
    

}