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
#include "readfile.h"
#include "variables.h"
#include "Ray.h"

// main function below

int main(int argc, const char * argv[]) {
    // insert code here...
    
    Scene *scene = new Scene(10,10);
    readfile(argv[1], scene);
    
    Sample* sample;
    sample = new Sample(0.0, 0.0);
    
    Sampler sampler = Sampler(scene->w,scene->h);
    Film film = Film(scene->w,scene->h);
    
    Color black = Color(0, 0, 0);
    Color red = Color(255, 0, 0);
    
    Ray *ray = new Ray(vec3(0,0,0), vec3(0,0,0), 0, 0, 100);
    
    // TODO: show progress
    while (sampler.getSample(sample)) {
        film.commit(*sample, black); // default black
        for (int i = 0; i < scene->num_objects; i++) {
            scene->camera->generateRay(*sample, ray, film);
            if (scene->shapes[i]->intersectP(*ray)) {
                film.commit(*sample, red); // if hit, draw red
            }
        }
    }
    
    film.writeImage();
    
    // release dynamically allocated memory
    delete sample;
    delete ray;
    
    for (int i = 0; i < scene->num_objects; i++) {
        delete scene->shapes[i];
    }
    delete [] scene->shapes;
    delete scene;
    
    return 0;
}
