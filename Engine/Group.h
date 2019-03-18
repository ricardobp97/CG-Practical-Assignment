//
// Created by andre on 17-03-2019.
//

#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H

#include <vector>
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

    std::vector<float> vertices;
    std::list<Group> childGroups;

public:
    Group();

    void setTranslate(float x, float y, float z);
    void setRotate(float angle, float axisX, float axisY, float axisZ);
    void setScale(float x, float y, float z);
    void setVertices(std::vector<float> v);
    void addGroup(Group g);

    float* getTranslate();
    float* getRotate();
    float* getScale();
    int getNextTransf();
    std::vector<float> getVertices();
    std::list<Group> getChildGroups();
};

#endif //ENGINE_GROUP_H