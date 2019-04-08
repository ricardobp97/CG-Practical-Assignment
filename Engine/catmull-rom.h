#ifndef ENGINE_CATMULL_ROM_H
#define ENGINE_CATMULL_ROM_H

void buildRotMatrix(float *x, float *y, float *z, float *m);

void cross(float *a, float *b, float *res);

void normalize(float *a);

float length(float *v);

void multMatrixVector(float *m, float *v, float *res);

void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);

void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv, std::map<int, float *> p);

#endif //ENGINE_CATMULL_ROM_H