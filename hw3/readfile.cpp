#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#include "readfile.h"

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