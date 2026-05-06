#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class MeshBuffer
{
public:
    GLuint VAO = 0;
    GLuint VBO = 0;
    GLuint EBO = 0;

    GLsizei vertexCount = 0;
    GLsizei indexCount = 0;
    bool useIndices = false;

    void setupVertices(const std::vector<Vertex>& vertices);
    void setupIndexed(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void setupPositions(const std::vector<glm::vec3>& positions);

    void drawArrays(GLenum mode) const;
    void drawElements(GLenum mode) const;

    void destroy();
};
