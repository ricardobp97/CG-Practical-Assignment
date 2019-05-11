#include <fstream>
#include "Model.h"
#include "Group.h"
#include "texture.h"

Model::Model() {
    has_color = false;
    colour_type = 0;

    has_textures = false;
}

void Model::storeVertices(const std::string &file) {
    float x, y, z;

    std::ifstream myFile;

    myFile.open(file);
    if (myFile.is_open()) {
        while (myFile.peek() != EOF) {
            myFile >> x >> y >> z;
            if(!myFile.fail()) {
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
            }
            myFile >> x >> y >> z;
            if(!myFile.fail()) {
                normals.push_back(x);
                normals.push_back(y);
                normals.push_back(z);
            }
            myFile >> x >> y;
            if(!myFile.fail()) {
                textures.push_back(x);
                textures.push_back(y);
            }
        }
        myFile.close();
    } else perror("Unable to open file");
}

void Model::setTextID(std::string file) {
    has_textures = true;
    textID = loadTexture(file);
}

void Model::setColour(int type, float *c) {
    has_color = true;

    colour_type = type;
    colour = c;
}

bool Model::hasTextures() {
    return has_textures;
}

std::vector<float> Model::getVertices() {
    return vertices;
}

std::vector<float> Model::getNormals() {
    return normals;
}

std::vector<float> Model::getTextures() {
    return textures;
}

int Model::getTextID() {
    return textID;
}
