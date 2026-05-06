#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

class CubeMap
{
public:
    GLuint textureID = 0;
    bool isLoaded = false;

    bool load(const std::vector<std::string>& faces);
    void bind() const;
    void Delete() const;
};