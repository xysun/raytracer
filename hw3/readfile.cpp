#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#include "readfile.h"
#include "Transform.h"

bool readvals(stringstream &s, const int numvals, float* values)
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true; 
}


void readfile(const char* filename, Scene *scene)
{
    string str, cmd;
    ifstream in;
    in.open(filename);
    
    if (in.is_open()) {
        getline (in, str);
        
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines
                
                stringstream s(str);
                s >> cmd;
                
                float values[10];
                bool validinput;
                
                if (cmd == "size") {
                    validinput = readvals(s,2,values);
                    if (validinput) {
                        scene->w = (int) values[0];
                        scene->h = (int) values[1];
                    }
                }else if (cmd == "camera"){
                    validinput = readvals(s, 10, values);
                    if (validinput){
                        vec3 lookFrom = vec3(values[0], values[1], values[2]);
                        vec3 lookAt = vec3(values[3], values[4], values[5]);
                        scene->camera->lookFrom = lookFrom;
                        scene->camera->lookAt = lookAt;
                        scene->camera->fovy = values[9];
                        vec3 zvec = lookFrom - lookAt;
                        scene->camera->up = Transform::upvector(vec3(values[6], values[7], values[8]), zvec);
                        
                        scene->camera->setCoord();
                    }
                }else if (cmd == "sphere"){
                    if (scene->num_objects < max_objects){
                        validinput = readvals(s, 4, values);
                        scene->shapes[scene->num_objects] = new Sphere(vec3(values[0], values[1], values[2]), values[3]);
                        scene->num_objects += 1;
                    }else{
                        printf("max number of objects reached\n");
                    }
                    
                }
            }
            getline (in, str);
        }
    }
    else {
        cerr << "Unable to Open Input Data File " << filename << "\n";
        throw 2;
    }
}