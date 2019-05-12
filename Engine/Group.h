#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H

#include <vector>
#include <map>
#include <list>
#include "Model.h"

#define TRANSLATE 1
#define ROTATE 2
#define SCALE 3

class Group {
    float* translate;
    float* rotate;
    float* scale;

    int* order;
    int n_order;
    int next_order;

    std::map<int, float*> pointsCatmull;
    bool transCatmull;
    bool rotateCatmull;
    float time_translate;

    std::vector<float> catmullCurve;

    std::list<Group> childGroups;
    std::list<Model> models;

public:
    Group();

    void setTranslate(float x, float y, float z);
    void setRotate(float angle, float axisX, float axisY, float axisZ);
    void setScale(float x, float y, float z);
    void addChildGroup(const Group& g);
    void addModel(const Model& m);
    void setTranslateCatmull(float time, std::map<int, float *> pointsCatmull, std::vector<float> curve);
    void setRotateCatmull(float time, float axisX, float axisY, float axisZ);

    float* getTranslate();
    float* getRotate();
    float* getScale();
    std::map<int, float *> getPointsCatmull();
    bool isTransCatmull();
    bool isRotateCatmull();
    float getTime();
    int getNextTransf();
    std::vector<float> getCatmullCurve();
    std::list<Group> getChildGroups();
    std::list<Model> getModels();
};

#endif //ENGINE_GROUP_H