#include <gtest/gtest.h>
#include "Sampler.h"

TEST(SamplerTest, ReturnCorrectSample) {
    
    Sampler sampler = Sampler(2,2);
    
    Sample *sample;
    
    // 1. (0.5,0.5)
    EXPECT_EQ(sampler.getSample(sample), true);
    EXPECT_EQ(sample->x, 0.5);
    EXPECT_EQ(sample->y, 0.5);
    
    // 2. (1.5, 0.5)
    EXPECT_EQ(sampler.getSample(sample), true);
    EXPECT_EQ(sample->x, 1.5);
    EXPECT_EQ(sample->y, 0.5);
    
    // 3. (0.5, 1.5)
    EXPECT_EQ(sampler.getSample(sample), true);
    EXPECT_EQ(sample->x, 0.5);
    EXPECT_EQ(sample->y, 1.5);
    
    // 4. (1.5, 1.5)
    EXPECT_EQ(sampler.getSample(sample), true);
    EXPECT_EQ(sample->x, 1.5);
    EXPECT_EQ(sample->y, 1.5);
    
    // 5. false
    EXPECT_EQ(sampler.getSample(sample), false);
    
}