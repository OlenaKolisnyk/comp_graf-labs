#include "CurveMode.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <algorithm>

#include "../core/Shader.h"

CurveMode::CurveMode()
{
    tess = 100;

    controlPoints = {
        { -0.8f,  0.0f, 0.0f },
        { -0.4f,  0.8f, 0.0f },
        {  0.4f,  0.8f, 0.0f },
        {  0.8f,  0.0f, 0.0f }
    };

    setupBuffers();
}

CurveMode::~CurveMode()
{
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}

void CurveMode::setupBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 controlPoints.size() * sizeof(glm::vec3),
                 controlPoints.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void CurveMode::onKey(int key, int /*scancode*/, int action, int /*mods*/)
{
    if (action != GLFW_PRESS && action != GLFW_REPEAT)
        return;

    // '+' на основній клавіатурі зазвичай це '=' з Shift
    if (key == GLFW_KEY_EQUAL || key == GLFW_KEY_KP_ADD)
        tess += 10;

    if (key == GLFW_KEY_MINUS || key == GLFW_KEY_KP_SUBTRACT)
        tess = std::max(1, tess - 10);
}

void CurveMode::draw(Shader& shader, const glm::mat4& MVP)
{
    shader.use();
    shader.setMat4("MVP", MVP);

    // Передати tess у TCS (як uniform)
    //  uTess  у curve.tcs як "uniform float uTess;"
    int loc = glGetUniformLocation(shader.ID, "uTess");
    if (loc >= 0)
        glUniform1f(loc, (float)tess);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    glBindVertexArray(VAO);
    glDrawArrays(GL_PATCHES, 0, 4);
    glBindVertexArray(0);
}