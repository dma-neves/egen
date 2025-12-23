#ifndef EGEN_WINDOW_H
#define EGEN_WINDOW_H

#include "opengl/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

namespace egen::window
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

#endif //EGEN_WINDOW_H
