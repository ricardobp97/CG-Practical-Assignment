#ifndef ENGINE_PARSE_H
#define ENGINE_PARSE_H

#include "include/pugixml.hpp"
#include "Group.h"
#include <list>

extern std::list<Group> groups;

Group group_xml(pugi::xml_node group);

void xml(std::string string);

void storeVertices(Group *g, std::string file);

#endif