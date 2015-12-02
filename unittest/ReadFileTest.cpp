#include <gtest/gtest.h>
#include "readfile.h"


TEST(ReadFileTest, ReadCorrectValues) {

    Scene *scene = new Scene(10,10);
    
    readfile("/Users/jsun/code/ucsd/hw3/unittest/readfile.txt", scene);
    
    // window
    EXPECT_EQ(scene->w, 100);
    EXPECT_EQ(scene->h, 100);
    
    // camera
    EXPECT_EQ(scene->camera->up, vec3(0,1,0));
    EXPECT_EQ(scene->camera->lookFrom, vec3(0,0,2));
    EXPECT_EQ(scene->camera->lookAt, vec3(0,0,0));
    EXPECT_EQ(scene->camera->fovy, 90);
    
    // shapes
    EXPECT_EQ(scene->num_objects, 2);
    
    // sphere1
    Sphere *sphere = dynamic_cast<Sphere*>(scene->shapes[0]);
    EXPECT_EQ(sphere->center, vec3(1,2,3));
    EXPECT_EQ(sphere->radius, 4);
    
    // sphere2
    Sphere *sphere2 = dynamic_cast<Sphere*>(scene->shapes[1]);
    EXPECT_EQ(sphere2->center, vec3(5,6,7));
    EXPECT_EQ(sphere2->radius, 8);
    
    // light
    EXPECT_EQ(scene->num_lights, 2);
    // ambient
    AmbientLight *light1 = dynamic_cast<AmbientLight*>(scene->lights[0]);
    EXPECT_EQ(light1->color.r, 10);
    EXPECT_EQ(light1->color.g, 20);
    EXPECT_EQ(light1->color.b, 30);
    
    // point light
    PointLight *light2 = dynamic_cast<PointLight*>(scene->lights[1]);
    EXPECT_EQ(light2->position.x, 0);
    EXPECT_EQ(light2->position.y, 1);
    EXPECT_EQ(light2->position.z, 2);
    EXPECT_EQ(light2->color.r, 10);
    EXPECT_EQ(light2->color.g, 20);
    EXPECT_EQ(light2->color.b, 30);
    

}