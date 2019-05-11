#ifndef ENGINE_LIGHTS_H
#define ENGINE_LIGHTS_H

#define POINT 1
#define DIRECTIONAL 2
#define SPOT 3

class Light {
    int type;
    float *param;

public:
    Light(int t, float *p);

    int getType();

    float *getParam();
};


#endif //ENGINE_LIGHTS_H
