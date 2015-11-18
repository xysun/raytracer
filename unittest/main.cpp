//
//  main.cpp
//  unittest
//
//  Created by Sun, Joy (Agoda) on 11/18/2558 BE.
//  Copyright © 2558 Sun, Joy (Agoda). All rights reserved.
//

#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}