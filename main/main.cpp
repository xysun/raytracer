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
    sample = new Sample(0.0, 0.0);
    
    Sampler sampler = Sampler(w,h);
    Film film = Film(w,h);
    
    Color black = Color(0, 0, 0);
    
    while (sampler.getSample(sample)) {
        film.commit(*sample, black);
    }
    
    film.writeImage();
    
    return 0;
}
