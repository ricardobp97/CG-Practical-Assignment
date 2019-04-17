#ifndef ENGINE_PARSE_H
#define ENGINE_PARSE_H

#include "include/pugixml.hpp"
#include "Group.h"

extern std::list<Group> groups;
extern int nBuffers;

Group group_xml(pugi::xml_node group);

void xml(std::string string);

void storeVertices(Group *g, const std::string& file);

#endif