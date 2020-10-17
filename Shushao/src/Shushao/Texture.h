#pragma once

#include "Object.h"
#include "Resource.h"

namespace se {

class Texture : public Object, public Resource {
public:
    Texture(std::string filename = "", std::string n = "");

    ~Texture();

    int height;
    int width;
    glm::vec2 size;
    int textureFormat;

    bool Load(std::string);
    bool LoadEmbedded(int IDRES, std::string library = "");
    bool LoadBytes(std::vector<char> data);

    unsigned int GetTextureID();
    unsigned int TextureID = 0;

private:
    void Bind(unsigned char* image_);
};

}  // namespace se