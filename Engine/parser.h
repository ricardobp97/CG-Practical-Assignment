#ifndef ENGINE_PARSE_H
#define ENGINE_PARSE_H

#include "include/pugixml.hpp"
#include "Group.h"
#include "Light.h"

extern std::list<Group> groups;
extern std::list<Light> lights;

extern int vert_nBuffers;
extern int text_nBuffers;

void xml(const std::string& string);

Group group_xml(pugi::xml_node group);

void light_xml(pugi::xml_node light);

#endif