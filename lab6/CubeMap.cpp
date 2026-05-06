#include "CubeMap.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

bool CubeMap::load(const std::vector<std::string>& faces)
{
    if (faces.size() != 6)
    {
        std::cout << "Cubemap needs exactly 6 texture files." << std::endl;
        return false;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(
            faces[i].c_str(),
            &width,
            &height,
            &nrChannels,
            0
        );

        if (data)
        {
            GLenum format = GL_RGB;

            if (nrChannels == 4)
                format = GL_RGBA;

            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                format,
                width,
                height,
                0,
                format,
                GL_UNSIGNED_BYTE,
                data
            );

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load: "
                << faces[i] << std::endl;

            stbi_image_free(data);
            return false;
        }
    }
    //налаштування параметрів текстури
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    isLoaded = true;
    return true;
}

void CubeMap::bind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

void CubeMap::Delete() const
{
    if (textureID != 0)
        glDeleteTextures(1, &textureID);
}