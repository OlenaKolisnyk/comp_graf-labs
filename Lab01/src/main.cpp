#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "core/Shader.h"
#include "modes/CurveMode.h"

// Глобальний вказівник для callback
static CurveMode* gCurve = nullptr;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    // Передаємо тільки (key, scancode, action, mods)
    if (gCurve)
        gCurve->onKey(key, scancode, action, mods);
}

int main()
{
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int W = 800, H = 600;
    GLFWwindow* window = glfwCreateWindow(W, H, "Lab01 - Curves", nullptr, nullptr);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW init failed\n";
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // MVP
    glm::mat4 proj  = glm::perspective(glm::radians(45.0f), float(W) / float(H), 0.1f, 100.0f);
    glm::mat4 view  = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 MVP   = proj * view * model;

    // Шейдер (шляхи під твою структуру: shaders/)
    Shader shader("shaders/vert.glsl",
                  "shaders/curve.tcs",
                  "shaders/curve.tes",
                  "shaders/frag.glsl");

    CurveMode curve;
    gCurve = &curve;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // CurveMode  викликає shader.use() і передає MVP
        curve.draw(shader, MVP);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    gCurve = nullptr;
    glfwTerminate();
    return 0;
}