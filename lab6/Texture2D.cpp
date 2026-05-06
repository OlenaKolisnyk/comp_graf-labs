#include "Texture2D.h"

#include <iostream>

bool Texture2D::generate_quads_texture(unsigned char* data, const unsigned int width, const unsigned int height)
{
     // TODO:
    // Реалізувати створення 2D-текстури
    
    // Формування текстури

   
    // Створення texture object

   

    std::cout << "Texture generation is not implemented yet."
        << std::endl;

    return false;
}

    void Texture2D::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    void Texture2D::Delete() const
    {
        if (textureID != 0)
            glDeleteTextures(1, &textureID);
    }



