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
                
                // initialize variables
                
                float values[10];
                bool validinput;
                float diffuse[3];
                float shininess;
                float specular[3];
                int max_vertices;
                vec3 *vertices;
                
                
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
                }else if(cmd == "diffuse"){
                    validinput = readvals(s, 3, values);
                    diffuse[0] = values[0];
                    diffuse[1] = values[1];
                    diffuse[2] = values[2];
                }
                else if (cmd == "shininess"){
                    validinput = readvals(s, 1, values);
                    shininess = values[0];
                }
                else if (cmd == "specular"){
                    validinput = readvals(s, 3, values);
                    specular[0] = values[0];
                    specular[1] = values[1];
                    specular[2] = values[2];
                }
                else if (cmd == "sphere"){
                    if (scene->num_objects < max_objects){
                        validinput = readvals(s, 4, values);
                        scene->shapes[scene->num_objects] = new Sphere(vec3(values[0], values[1], values[2]), values[3]);
                        // set material
                        scene->shapes[scene->num_objects]->set_diffuse(diffuse);
                        scene->shapes[scene->num_objects]->set_shininess(shininess);
                        scene->shapes[scene->num_objects]->set_specular(specular);
                        scene->num_objects += 1;
                    }else{
                        printf("max number of objects reached\n");
                    }
                    
                }else if (cmd == "ambient"){
                    if (scene->num_lights < max_lights) {
                        validinput = readvals(s, 3, values);
                        scene->lights[scene->num_lights] = new AmbientLight(Color(values[0], values[1], values[2]));
                        scene->num_lights += 1;
                    }else{
                        printf("max number of lights reached\n");
                    }
                }else if (cmd == "point"){
                    if (scene->num_lights < max_lights) {
                        validinput = readvals(s, 6, values);
                        vec3 pos = vec3(values[0], values[1], values[2]);
                        Color color = Color(values[3], values[4], values[5]);
                        scene->lights[scene->num_lights] = new PointLight(color, pos);
                        scene->num_lights += 1;
                    }else{
                        printf("max number of lights reached\n");
                    }
                }
                else if (cmd == "directional"){
                    if (scene->num_lights < max_lights) {
                        validinput = readvals(s, 6, values);
                        vec3 pos = vec3(values[0], values[1], values[2]);
                        Color color = Color(values[3], values[4], values[5]);
                        scene->lights[scene->num_lights] = new DirectionalLight(color, pos);
                        scene->num_lights += 1;
                    }else{
                        printf("max number of lights reached\n");
                    }
                }
                else if (cmd == "maxverts"){
                    validinput = readvals(s, 1, values);
                    max_vertices = (int)values[0];
                    scene->max_vertices = max_vertices;
                }
                else if (cmd == "vertex"){
                    validinput = readvals(s, 3, values);
                    if (scene->current_vertex >= scene->max_vertices){
                        printf("max number of vertices reached\n");
                    }else{
                        scene->vertices[scene->current_vertex] = vec3(values[0], values[1], values[2]);
                        scene->current_vertex += 1;
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