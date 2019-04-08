#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H

#include <vector>
#include <map>
#include <list>

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
    bool transCatmull = false;
    bool rotateCatmull = false;
    float time;

    std::vector<float> vertices;
    std::list<Group> childGroups;

public:
    Group();

    void setTranslate(float x, float y, float z);
    void setRotate(float angle, float axisX, float axisY, float axisZ);
    void setScale(float x, float y, float z);
    void setVertices(std::vector<float> v);
    void addChildGroup(Group g);
    void setTranslateCatmull(float time, std::map<int, float *> pointsCatmull);

    float* getTranslate();
    float* getRotate();
    float* getScale();
    std::map<int, float *> getPointsCatmull();
    bool isTransCatmull();
    bool isRotateCatmull();
    float getTime();
    int getNextTransf();
    std::vector<float> getVertices();
    std::list<Group> getChildGroups();
};

#endif //ENGINE_GROUP_H