//
//  main.cpp
//  main
//
//  Created by Sun, Joy (Agoda) on 11/18/2558 BE.
//  Copyright © 2558 Sun, Joy (Agoda). All rights reserved.
//

//
//  main.cpp
//  hw3
//
//  Created by Sun, Joy (Agoda) on 11/16/2558 BE.
//  Copyright © 2558 Sun, Joy (Agoda). All rights reserved.
//

#include <iostream>
#include <FreeImage.h>

#include "Film.h"

// main function below

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int w = 100;
    int h = 100;
    
    Sample* sample;
    
    Sampler sampler = Sampler(w,h);
    
    while (sampler.getSample(sample)) {
        ;
    }
    
    // test free image
    FreeImage_Initialise();
    
    FreeImage_DeInitialise();
    
    std::cout << "Hello, World!\n";
    return 0;
}
