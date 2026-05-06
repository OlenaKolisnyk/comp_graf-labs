#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>



std::string readShaderFromFile(const char* filename);

class Shader {
public:
    GLuint ID = 0;
    bool isValid = false;
    Shader(const char* vertsFile, const char* fragmFile);
    void Use() const;
    void Delete() const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
};
