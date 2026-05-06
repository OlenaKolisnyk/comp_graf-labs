#pragma once
#include <GL/glew.h>

class Texture2D
{
public:
    GLuint textureID = 0;
    bool isLoaded = false;

    bool generate_quads_texture(unsigned char* data, const unsigned int width, const unsigned int height);
    

    void bind() const;

    void Delete() const;
};
