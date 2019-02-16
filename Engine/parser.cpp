#include <string>
#include <iostream>
#include <vector>

#include "parser.h"

std::vector<std::string> files_list;

void xml(std::string xml_name) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml_name.c_str());

    if (result) {
        /** <scene> **/
        pugi::xml_node scene = doc.child("scene");

        for (pugi::xml_node scene_child = scene.first_child(); scene_child; scene_child = scene_child.next_sibling()) {
            /** <group> **/
            if (scene_child.name() == std::string("group")) {
                group_xml(scene_child);
            }
        }
    } else perror("Unable to open file");
}

void group_xml(pugi::xml_node group) {
    bool flag_models = false;

    for (pugi::xml_node group_child = group.first_child(); group_child; group_child = group_child.next_sibling()) {

        /** <group> **/
        if (group_child.name() == std::string("group")) {
            group_xml(group_child);
        }

        /** <models> **/
        if (group_child.name() == std::string("models") && !flag_models) {
            flag_models = true;
            for (pugi::xml_node models_child = group_child.first_child(); models_child; models_child = models_child.next_sibling()) {

                /** <model/> **/
                if (models_child.name() == std::string("model")) {
                    files_list.emplace_back(models_child.attribute("file").value());
                }
            }
        }
    }
}