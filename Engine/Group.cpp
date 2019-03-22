//
// Created by andre on 17-03-2019.
//

#include "Group.h"

Group::Group() {
    translate = rotate = scale = nullptr;

    order = new int[3];
    n_order = 0;
    next_order = 0;

    for (int i = 0; i < 3; i++)
        order[i] = 0;
}

void Group::setTranslate(float x, float y, float z) {
    order[n_order++] = TRANSLATE;

    translate = new float[3];
    translate[0] = x;
    translate[1] = y;
    translate[2] = z;
}

void Group::setRotate(float angle, float axisX, float axisY, float axisZ) {
    order[n_order++] = ROTATE;

    rotate = new float[4];
    rotate[0] = angle;
    rotate[1] = axisX;
    rotate[2] = axisY;
    rotate[3] = axisZ;
}

void Group::setScale(float x, float y, float z) {
    order[n_order++] = SCALE;

    scale = new float[3];
    scale[0] = x;
    scale[1] = y;
    scale[2] = z;
}

void Group::setVertices(std::vector<float> v) {
    vertices.insert(std::end(vertices), std::begin(v), std::end(v));
}

void Group::addGroup(Group g) {
    childGroups.push_back(g);
}

float *Group::getTranslate() {
    return translate;
}

float *Group::getRotate() {
    return rotate;
}

float *Group::getScale() {
    return scale;
}

int Group::getNextTransf() {
    if (next_order == 3) return 0;
    return order[next_order++];
}

std::vector<float> Group::getVertices() {
    return vertices;
}

std::list<Group> Group::getChildGroups() {
    return childGroups;
}