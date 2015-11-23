#include <gtest/gtest.h>
#include "readfile.h"


TEST(ReadFileTest, ReadCorrectValues) {

    Scene *scene = new Scene(10,10);
    
    readfile("/Users/jsun/code/ucsd/hw3/unittest/readfile.txt", scene);
    
    EXPECT_EQ(scene->w, 100);
    EXPECT_EQ(scene->h, 100);
    

}