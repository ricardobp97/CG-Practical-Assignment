#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

#include "parser.h"

std::list<Group> groups = std::list<Group>();

void xml(std::string xml_name) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml_name.c_str());

    if (result) {
        /** <scene> **/
        pugi::xml_node scene = doc.child("scene");

        for (pugi::xml_node scene_child = scene.first_child(); scene_child; scene_child = scene_child.next_sibling()) {
            /** <group> **/
            if (scene_child.name() == std::string("group")) {
                groups.push_back(group_xml(scene_child));
            }
        }
    } else perror("Unable to open file");
}

Group group_xml(pugi::xml_node group) {
    auto *g = new Group();
    bool flag_models = false;

    for (pugi::xml_node group_child = group.first_child(); group_child; group_child = group_child.next_sibling()) {

        /** <group> **/
        if (group_child.name() == std::string("group")) {
            g->addChildGroup(group_xml(group_child));
        }

        /** <models> **/
        if (group_child.name() == std::string("models") && !flag_models) {
            flag_models = true;
            for (pugi::xml_node models_child = group_child.first_child(); models_child; models_child = models_child.next_sibling()) {
                /** <model/> **/
                if (models_child.name() == std::string("model")) {
                    storeVertices(g, models_child.attribute("file").value());
                }
            }
        }

        /** <translate/> **/
        if (group_child.name() == std::string("translate")) {
            pugi::xml_node translate = group_child;
            g->setTranslate(std::stof(translate.attribute("X").value()),
                            std::stof(translate.attribute("Y").value()),
                            std::stof(translate.attribute("Z").value()));
        }

        /** <rotate/> **/
        if (group_child.name() == std::string("rotate")) {
            pugi::xml_node rotate = group_child;
            g->setRotate(std::stof(rotate.attribute("angle").value()),
                         std::stof(rotate.attribute("axisX").value()),
                         std::stof(rotate.attribute("axisY").value()),
                         std::stof(rotate.attribute("axisZ").value()));
        }

        /** <scale/> **/
        if (group_child.name() == std::string("scale")) {
            pugi::xml_node scale = group_child;
            g->setScale(std::stof(scale.attribute("X").value()),
                        std::stof(scale.attribute("Y").value()),
                        std::stof(scale.attribute("Z").value()));
        }
    }
    return *g;
}

void storeVertices(Group *g, std::string file) {
    float x, y, z;
    std::vector<float> aux;

    std::ifstream myFile;

    myFile.open(file);
    if (myFile.is_open()) {
        while (myFile >> x >> y >> z) {
            aux.push_back(x);
            aux.push_back(y);
            aux.push_back(z);
        }
        myFile.close();

        g->setVertices(aux);
    } else perror("Unable to open file");
}
