#include <string>
#include <iostream>
#include <vector>

#include "parser.h"

std::vector<std::string> files_list;

void xml(std::string xml_name) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml_name.c_str());

    if (result) {
        pugi::xml_node scene = doc.child("scene");

        for (pugi::xml_node scene_child = scene.first_child(); scene_child; scene_child = scene_child.next_sibling()) {
            if (scene_child.name() == std::string("model")) {
                files_list.emplace_back(scene_child.attribute("file").value());
            }
        }
    } else perror("Unable to open file");
}
