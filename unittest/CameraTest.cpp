#include <gtest/gtest.h>
#include "Camera.h"
#include "Ray.h"
#include "variables.h"

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
    Camera c = Camera(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0), 90);
    Film film = Film(2, 2);
    Sample sample = Sample(0, 0);
    
    Ray *ray = new Ray(vec4(0,0,0,1), vec4(0,0,0,0), 0, 0, 100);
    
    c.generateRay(sample, ray, film);
    
    EXPECT_EQ(ray->pos.x, 0);
    EXPECT_EQ(ray->pos.y, 0);
    EXPECT_EQ(ray->pos.z, 1);
    
    // dir
    vec3 dir = glm::normalize(vec3(-1,1,-1));
    EXPECT_EQ(ray->dir.x, dir.x);
    EXPECT_EQ(ray->dir.y, dir.y);
    EXPECT_EQ(ray->dir.z, dir.z);
    
    // another point
    Sample sample2 = Sample(2,0);
    
    c.generateRay(sample2, ray, film);
    
    vec3 dir2 = glm::normalize(vec3(1,1,-1));
    EXPECT_EQ(ray->dir.x, dir2.x);
    EXPECT_EQ(ray->dir.y, dir2.y);
    EXPECT_EQ(ray->dir.z, dir2.z);
    
    
}