#pragma once

#include "opengl/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

namespace egen
{

class Window 
{
public:

    int init();
    void terminate();
    GLFWwindow* get();

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    GLFWwindow *m_window;
};

}