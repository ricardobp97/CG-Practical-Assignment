#ifndef ENGINE_MODELS_H
#define ENGINE_MODELS_H

#include <vector>

#define DIFFUSE 1
#define SPECULAR 2
#define EMISSIVE 3
#define AMBIENT 4

class Model {
    bool has_color;
    int colour_type;
    float *colour;

    std::vector<float> vertices;

    bool has_textures;
    int textID;
    std::vector<float> textures;

    std::vector<float> normals;

public:
    Model();

    void storeVertices(const std::string &file);

    void setTextID(std::string file);

    void setColour(int type, float *c);

    bool hasTextures();

    std::vector<float> getVertices();

    std::vector<float> getNormals();

    std::vector<float> getTextures();

    int getTextID();
};

#endif //ENGINE_MODELS_H
