#ifndef ENGINE_PARSE_H
#define ENGINE_PARSE_H

#include "include/pugixml.hpp"

extern std::vector<std::string> files_list;

void group_xml(pugi::xml_node group);
void xml(std::string string);

#endif