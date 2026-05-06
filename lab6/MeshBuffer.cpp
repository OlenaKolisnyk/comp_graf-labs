#include "MeshBuffer.h"
#include <cstddef>

void MeshBuffer::setupVertices(const std::vector<Vertex>& vertices)
{
    destroy();

    vertexCount = static_cast<GLsizei>(vertices.size());
    indexCount = 0;
    useIndices = false;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(2);

    // texture coordinates
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

void MeshBuffer::setupIndexed(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
    destroy();

    vertexCount = static_cast<GLsizei>(vertices.size());
    indexCount = static_cast<GLsizei>(indices.size());
    useIndices = true;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(Vertex),
        vertices.data(),
        GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int),
        indices.data(),
        GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(2);

    // texture coordinates
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}

//Створення буфера  для skybox / cube-map
void MeshBuffer::setupPositions(const std::vector<glm::vec3>& positions)
{
    // Видалення попередніх буферів
    destroy();

    // виклик кількості вершин
    vertexCount = static_cast<GLsizei>(positions.size());

    // Індекси не використовуються
    indexCount = 0;
    useIndices = false;
    // Створення VAO та VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // Активація VAO
    glBindVertexArray(VAO);
    // Завантаження вершин у VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
    // Налаштування vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    // Увімкнення attribute
    glEnableVertexAttribArray(0);

    // Відв'язування VAO
    glBindVertexArray(0);
}
// Малювання без індексів
// OpenGL читає вершини послідовно з VBO
void MeshBuffer::drawArrays(GLenum mode) const
{
    // Перевірка, чи VAO створений
    // і чи є вершини для малювання
    if (VAO == 0 || vertexCount == 0)
        return;

    // Активація VAO
    glBindVertexArray(VAO);
    glDrawArrays(mode, 0, vertexCount);

    // Відв'язування VAO
    glBindVertexArray(0);
}

// Малювання з використанням індексів
// OpenGL використовує EBO (index buffer)
void MeshBuffer::drawElements(GLenum mode) const
{
    // Перевірка наявності буферів та індексів
    if (VAO == 0 || EBO == 0 || indexCount == 0)
        return;

    // Активація VAO
    glBindVertexArray(VAO);
    // Малювання за індексами
    glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);

    // Відв'язування VAO
    glBindVertexArray(0);
}

void MeshBuffer::destroy()
{
    if (EBO != 0)
    {
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }

    if (VBO != 0)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if (VAO != 0)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    vertexCount = 0;
    indexCount = 0;
    useIndices = false;
}