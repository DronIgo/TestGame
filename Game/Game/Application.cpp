#include "Application.h"
#include "Graphics/GL_include.h"
#include "Shortcut/shortcutInit.h"
#include "Utility/debugUtils.h"

#include <iostream>
#include <chrono>
#include <thread>

void initGLFW();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* window;
namespace {
    const unsigned int scrWidth = 800;
    const unsigned int scrHeight = 600;
}

int main() {
    initGLFW();
    initGraphics();
    initShaders();
    std::cout << glGetString(GL_VERSION) << std::endl;
    while (true) {

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void initGLFW() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(scrWidth, scrHeight, "Main_window", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glViewport(0, 0, scrWidth, scrHeight);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }
}