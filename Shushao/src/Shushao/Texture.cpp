#include "sepch.h"

#include <SOIL2.h>
#include <glad/glad.h>

#include "Resources.h"
#include "Utility.h"
#include "Texture.h"

#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A

namespace se {

Texture::Texture(std::string filename, std::string n) {
    if (filename != "") Load(filename);
    name = (n == "" ? util::basename(filename) : n);
}

Texture::~Texture() {
    const GLuint textures[] = { TextureID };
    glDeleteTextures(1, textures);
}

bool Texture::LoadEmbedded(int IDRES, std::string library) {
    std::vector<char> data = Resources::GetEmbeddedData(IDRES, library);
    return LoadBytes(data);
}

bool Texture::LoadBytes(std::vector<char> data) {
    //TextureID = SOIL_load_OGL_texture_from_memory(
    //    (const unsigned char*)&data[0],
    //    data.size(),
    //    SOIL_LOAD_AUTO,
    //    SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT  //
    //);

    // method 2
    unsigned char* image = SOIL_load_image_from_memory((const unsigned char*)&data[0], data.size(), &width, &height, 0, SOIL_LOAD_RGB);
    Bind(image);
    SOIL_free_image_data(image);

    return TextureID > 0;
#if 0
    SDL_RWops* rw = SDL_RWFromMem(&data[0], data.size());
    Surface = IMG_LoadPNG_RW(rw);

    if (Surface == nullptr) {
        Debug::Log(WARNING) << "Can't load embedded image '" << name << "': " << IMG_GetError() << std::endl;
        return false;
    }
    return Bind(Surface);
#endif
}

bool Texture::Load(std::string filename) {
    int components = 0;
    unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, &components, SOIL_LOAD_AUTO);

    if (image) {
        switch (components) {
        case 1:
            textureFormat = GL_LUMINANCE;
            break;
        case 2:
            textureFormat = GL_LUMINANCE_ALPHA;
            break;
        case 3:
            textureFormat = GL_RGB;
            break;
        case 4:
            textureFormat = GL_RGBA;
            break;
        default:
            textureFormat = GL_RGB;
            break;
        }
    } else {
        DEBUG_CORE_ERROR("Can't load image '" + filename + "'");
        return false;
    }

    Bind(image);
    SOIL_free_image_data(image);

    return TextureID > 0;
}

void Texture::Bind(unsigned char* image_) {
    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(textureFormat), width, height, 0, textureFormat, GL_UNSIGNED_BYTE, (GLvoid*)image_);

    // glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::GetTextureID() {
    return TextureID;
}
}  // namespace se
