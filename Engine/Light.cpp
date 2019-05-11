#include "Light.h"

Light::Light(int t, float *p) {
    type = t;

    if (type == POINT) {
        param = new float[4];

        param[0] = p[0];
        param[1] = p[1];
        param[2] = p[2];
        param[3] = 1;
    } else if (type == DIRECTIONAL) {
        param = new float[4];

        param[0] = p[0];
        param[1] = p[1];
        param[2] = p[2];
        param[3] = 0;
    } else if (type == SPOT) {
        param = new float[9];

        param[0] = p[0];
        param[1] = p[1];
        param[2] = p[2];
        param[3] = 1;
        param[4] = p[3];
        param[5] = p[4];
        param[6] = p[5];
        param[7] = p[6];
        param[8] = p[7];
    }
}

int Light::getType() {
    return type;
}

float *Light::getParam() {
    return param;
}