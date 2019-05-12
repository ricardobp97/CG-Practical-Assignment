#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

#include "parser.h"
#include "catmull-rom.h"
#include "Model.h"
#include "Light.h"

std::list<Group> groups = std::list<Group>();
std::list<Light> lights = std::list<Light>();

int vert_nBuffers = 0;
int text_nBuffers = 0;

void xml(const std::string &xml_name) {
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
            /** <lights> **/
            if (scene_child.name() == std::string("lights")) {
                light_xml(scene_child);
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
            auto *m = new Model();
            flag_models = true;
            for (pugi::xml_node models_child = group_child.first_child(); models_child; models_child = models_child.next_sibling()) {
                /** <model/> **/
                if (models_child.name() == std::string("model")) {
                    vert_nBuffers++;
                    m->storeVertices(models_child.attribute("file").value());

                    if (models_child.attribute("texture").name() == std::string("texture")) {
                        text_nBuffers++;
                        m->setTextID(models_child.attribute("texture").value());
                    }

                    if (models_child.attribute("diffR").name() == std::string("diffR")) {
                        auto *colour = new float[3];
                        colour[0] = std::stof(models_child.attribute("diffR").value());
                        colour[1] = std::stof(models_child.attribute("diffG").value());
                        colour[2] = std::stof(models_child.attribute("diffB").value());

                        m->setColour(DIFFUSE, colour);
                    }

                    if (models_child.attribute("specR").name() == std::string("specR")) {
                        auto *colour = new float[3];
                        colour[0] = std::stof(models_child.attribute("specR").value());
                        colour[1] = std::stof(models_child.attribute("specG").value());
                        colour[2] = std::stof(models_child.attribute("specB").value());

                        m->setColour(SPECULAR, colour);
                    }

                    if (models_child.attribute("emisR").name() == std::string("emisR")) {
                        auto *colour = new float[4];
                        colour[0] = std::stof(models_child.attribute("emisR").value());
                        colour[1] = std::stof(models_child.attribute("emisG").value());
                        colour[2] = std::stof(models_child.attribute("emisB").value());
                        colour[3] = 1;

                        m->setColour(EMISSIVE, colour);
                    }

                    if (models_child.attribute("ambiR").name() == std::string("ambiR")) {
                        auto *colour = new float[3];
                        colour[0] = std::stof(models_child.attribute("ambiR").value());
                        colour[1] = std::stof(models_child.attribute("ambiG").value());
                        colour[2] = std::stof(models_child.attribute("ambiB").value());

                        m->setColour(AMBIENT, colour);
                    }
                    g->addModel(*m);
                }
            }
        }

        /** <translate/> **/
        if (group_child.name() == std::string("translate")) {
            pugi::xml_node translate = group_child;

            if (translate.attribute("time")) {
                vert_nBuffers++;
                float *p;
                float time = std::stof(translate.attribute("time").value());
                std::map<int, float *> pointsCatmull = std::map<int, float *>();
                int i = 0;

                for (pugi::xml_node catmull = translate.first_child(); catmull; catmull = catmull.next_sibling()) {
                    p = new float[3];
                    p[0] = std::stof(catmull.attribute("X").value());
                    p[1] = std::stof(catmull.attribute("Y").value());
                    p[2] = std::stof(catmull.attribute("Z").value());
                    pointsCatmull.insert(std::make_pair(i, p));
                    i++;
                }

                float alpha = 1.0f / (pointsCatmull.size() * 50);
                std::vector<float> curve;

                for (float gt = 0; gt < 1; gt += alpha) {
                    float pos[3];
                    float deriv[3];

                    getGlobalCatmullRomPoint(gt, pos, deriv, pointsCatmull);
                    curve.push_back(pos[0]);
                    curve.push_back(pos[1]);
                    curve.push_back(pos[2]);
                }
                g->setTranslateCatmull(time, pointsCatmull, curve);
            } else {
                g->setTranslate(std::stof(translate.attribute("X").value()),
                                std::stof(translate.attribute("Y").value()),
                                std::stof(translate.attribute("Z").value()));
            }
        }

        /** <rotate/> **/
        if (group_child.name() == std::string("rotate")) {
            pugi::xml_node rotate = group_child;

            if (rotate.attribute("time")) {
                g->setRotateCatmull(std::stof(rotate.attribute("time").value()),
                                    std::stof(rotate.attribute("axisX").value()),
                                    std::stof(rotate.attribute("axisY").value()),
                                    std::stof(rotate.attribute("axisZ").value()));

            } else {
                g->setRotate(std::stof(rotate.attribute("angle").value()),
                             std::stof(rotate.attribute("axisX").value()),
                             std::stof(rotate.attribute("axisY").value()),
                             std::stof(rotate.attribute("axisZ").value()));
            }
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

void light_xml(pugi::xml_node light) {
    Light *l = nullptr;

    for (pugi::xml_node light_child = light.first_child(); light_child; light_child = light_child.next_sibling()) {
        if (light_child.attribute("type").value() == std::string("POINT")) {
            float param[3];
            param[0] = std::stof(light_child.attribute("posX").value());
            param[1] = std::stof(light_child.attribute("posY").value());
            param[2] = std::stof(light_child.attribute("posZ").value());

            l = new Light(POINT, param);
        } else if (light_child.attribute("type").value() == std::string("DIRECTIONAL")) {
            float param[3];
            param[0] = std::stof(light_child.attribute("dirX").value());
            param[1] = std::stof(light_child.attribute("dirY").value());
            param[2] = std::stof(light_child.attribute("dirZ").value());

            l = new Light(DIRECTIONAL, param);
        } else if (light_child.attribute("type").value() == std::string("SPOT")) {
            float param[8];
            param[0] = std::stof(light_child.attribute("posX").value());
            param[1] = std::stof(light_child.attribute("posY").value());
            param[2] = std::stof(light_child.attribute("posZ").value());
            param[3] = std::stof(light_child.attribute("dirX").value());
            param[4] = std::stof(light_child.attribute("dirY").value());
            param[5] = std::stof(light_child.attribute("dirZ").value());
            param[6] = std::stof(light_child.attribute("exp").value());
            param[7] = std::stof(light_child.attribute("cut").value());

            l = new Light(SPOT, param);
        }

        lights.push_back(*l);
    }
}
