#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "shaderClass.h"
#include "CubeMap.h"
#include "MeshBuffer.h"
//#include "Texture2D.h"
#include <vector>
#include <iostream>


// розміри вікна
int Wi = 800, Hi = 600;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << " x " << xpos << " y " << ypos << std::endl;
    return;
}

static void framebuffer_size_callback(GLFWwindow* window, int Wi, int Hi)
{
    glViewport(0, 0, Wi, Hi);
    std::cout << "Wi " << Wi << " Hi " << Hi << std::endl;
}
//список шляхів
std::vector<std::string> faces
{
    "skybox/right.jpg",
    "skybox/left.jpg",
    "skybox/top.jpg",
    "skybox/bottom.jpg",
    "skybox/front.jpg",
    "skybox/back.jpg"
};
std::vector<glm::vec3> skyboxVert =
{
    // back face
    {-1.0f,  1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f},

    { 1.0f, -1.0f, -1.0f},
    { 1.0f,  1.0f, -1.0f},
    {-1.0f,  1.0f, -1.0f},

    // left face
    {-1.0f, -1.0f,  1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f,  1.0f, -1.0f},

    {-1.0f,  1.0f, -1.0f},
    {-1.0f,  1.0f,  1.0f},
    {-1.0f, -1.0f,  1.0f},

    // right face
    { 1.0f, -1.0f, -1.0f},
    { 1.0f, -1.0f,  1.0f},
    { 1.0f,  1.0f,  1.0f},

    { 1.0f,  1.0f,  1.0f},
    { 1.0f,  1.0f, -1.0f},
    { 1.0f, -1.0f, -1.0f},

    // front face
    {-1.0f, -1.0f,  1.0f},
    {-1.0f,  1.0f,  1.0f},
    { 1.0f,  1.0f,  1.0f},

    { 1.0f,  1.0f,  1.0f},
    { 1.0f, -1.0f,  1.0f},
    {-1.0f, -1.0f,  1.0f},

    // top face
    {-1.0f,  1.0f, -1.0f},
    { 1.0f,  1.0f, -1.0f},
    { 1.0f,  1.0f,  1.0f},

    { 1.0f,  1.0f,  1.0f},
    {-1.0f,  1.0f,  1.0f},
    {-1.0f,  1.0f, -1.0f},

    // bottom face
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f,  1.0f},
    { 1.0f, -1.0f, -1.0f},

    { 1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f,  1.0f},
    { 1.0f, -1.0f,  1.0f}
};

std::vector<Vertex> vertices =
{
    // грань 1 (передня)      нормалі                      колір                текстури
    {{ 0.0f,  0.5f,  0.0f}, { 0.0f,  0.707f,  0.707f}, {1.0f, 0.0f, 0.0f}, {0.5f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, { 0.0f,  0.707f,  0.707f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, { 0.0f,  0.707f,  0.707f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

    // грань 2 (права)
    {{ 0.0f,  0.5f,  0.0f}, { 0.707f,  0.707f,  0.0f}, {0.0f, 1.0f, 0.0f}, {0.5f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, { 0.707f,  0.707f,  0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, { 0.707f,  0.707f,  0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},

    // грань 3 (задня)
    {{ 0.0f,  0.5f,  0.0f}, { 0.0f,  0.707f, -0.707f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, { 0.0f,  0.707f, -0.707f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, { 0.0f,  0.707f, -0.707f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},

    // грань 4 (ліва)
    {{ 0.0f,  0.5f,  0.0f}, {-0.707f,  0.707f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.5f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {-0.707f,  0.707f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {-0.707f,  0.707f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},

    // основа 1
    {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},

    // основа 2
    {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
};

int main(void)
{
    setlocale(LC_ALL, "Russian");

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(Wi, Hi, "GL", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "glew не ініціалізовано" << std::endl;
        glfwTerminate();
        system("pause");
        return -1;
    }
    MeshBuffer mesh;
    mesh.setupVertices(vertices);


    
    glViewport(0, 0, Wi, Hi);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    

    Shader shaderProgram("verts.vs", "fragm.fs");
    if (!shaderProgram.isValid)
    {
        std::cout << "Shader program was not created." << std::endl;
        glfwTerminate();
        return -1;
    }
    Shader skyboxShader("skybox.vs", "skybox.fs");

    if (!skyboxShader.isValid)
    {
        std::cout << "Skybox shader was not created." << std::endl;
        glfwTerminate();
        return -1;
    }
    MeshBuffer skyboxMesh;
    skyboxMesh.setupPositions(skyboxVert);

    CubeMap skyboxTexture;

    if (!skyboxTexture.load(faces))
    {
        std::cout << "Failed to load cubemap." << std::endl;
        return -1;
    }
    
    // Виклик текстури
    /*Texture2D texture;

    const unsigned int texWidth = 1000;
    const unsigned int texHeight = 1000;
    const unsigned int channels = 3;

    unsigned char* textureData = new unsigned char[texWidth * texHeight * channels];

    texture.generate_quads_texture(textureData, texWidth, texHeight);

    delete[] textureData;*/


    glm::mat4 view = glm::lookAt(
                glm::vec3(0.0f, 0.0f, 5.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
            );
    glEnable(GL_DEPTH_TEST);
    // Головний цикл
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)Wi / (float)Hi, 0.1f, 100.0f);

        shaderProgram.Use();
        

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));

        shaderProgram.setMat4("model", model);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("proj", proj);

        mesh.drawArrays(GL_TRIANGLES);
        
        // Малювання skybox
        glDepthFunc(GL_LEQUAL);

        skyboxShader.Use();

        glm::mat4 skyboxView = glm::mat4(glm::mat3(view));

        skyboxShader.setMat4("view", skyboxView);
        skyboxShader.setMat4("proj", proj);

        glActiveTexture(GL_TEXTURE0);
        skyboxTexture.bind();

        skyboxMesh.drawArrays(GL_TRIANGLES);

        glDepthFunc(GL_LESS);

        //малювання Texture2D
        /*glActiveTexture(GL_TEXTURE0);
        texture.bind();
        glUniform1i(glGetUniformLocation(shaderProgram.ID, "texture1"), 0);*/
        
       
        
       

        glfwSwapBuffers(window);
        glfwPollEvents();
    
    }

    
    shaderProgram.Delete();
    glfwTerminate();
    return 0;
}