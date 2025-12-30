#pragma once

#include <glm/glm.hpp>
#include <vector>

class Shader;

class CurveMode
{
public:
    CurveMode();
    ~CurveMode();

    void onKey(int key, int scancode, int action, int mods);
    void draw(Shader& shader, const glm::mat4& MVP);

private:
    void setupBuffers();

private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;

    int tess = 100;
    std::vector<glm::vec3> controlPoints;
};