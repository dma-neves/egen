#pragma once

#include "opengl/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <functional>

namespace egen
{

class Window 
{
public:

    Window(std::function<void(GLFWwindow *window)> key_input_callback);

    int init();
    void terminate();
    GLFWwindow* get();

    bool should_close();
    void process_inputs();

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    GLFWwindow *m_window;
    std::function<void(GLFWwindow *window)> m_key_input_callback;
};

}