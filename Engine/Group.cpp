#include "Group.h"

Group::Group() {
    translate = rotate = scale = nullptr;

    order = new int[3];
    n_order = 0;
    next_order = 0;

    transCatmull = false;
    rotateCatmull = false;
    time_translate = false;

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

void Group::setTranslateCatmull(float time, std::map<int, float *> p, std::vector<float> curve) {
    order[n_order++] = TRANSLATE;

    transCatmull = true;
    time_translate = time;
    pointsCatmull = std::move(p);
    catmullCurve = std::move(curve);
}

void Group::setRotate(float angle, float axisX, float axisY, float axisZ) {
    order[n_order++] = ROTATE;

    rotate = new float[4];
    rotate[0] = angle;
    rotate[1] = axisX;
    rotate[2] = axisY;
    rotate[3] = axisZ;
}

void Group::setRotateCatmull(float time, float axisX, float axisY, float axisZ) {
    order[n_order++] = ROTATE;
    rotateCatmull = true;

    rotate = new float[4];
    rotate[0] = time;
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

void Group::addChildGroup(const Group &g) {
    childGroups.push_back(g);
}

void Group::addModel(const Model &m) {
    models.push_back(m);
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

std::vector<float> Group::getCatmullCurve() {
    return catmullCurve;
}

std::list<Group> Group::getChildGroups() {
    return childGroups;
}

std::map<int, float *> Group::getPointsCatmull() {
    return pointsCatmull;
}

bool Group::isTransCatmull() {
    return transCatmull;
}

bool Group::isRotateCatmull() {
    return rotateCatmull;
}

float Group::getTime() {
    return time_translate;
}

std::list<Model> Group::getModels() {
    return models;
}
