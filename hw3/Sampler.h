class Sample{
public:
    float x,y;
    Sample(float, float); // declaration
};


class Sampler{
    // topleft is (0,0), bottom right is (width, height)
    int width, height, pixels, current_pixel;
public:
    Sampler(int, int);
    bool getSample(Sample* sample);
};

