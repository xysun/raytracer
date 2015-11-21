#include "Sampler.h"
#include "Color.h"

class Film{
private:
    int w, h;
    unsigned char pixels[3*100*100] = {};
public:
    Film(int, int);
    void commit(Sample sample, Color color);
    void writeImage();
    unsigned char getPixel(int);
};