#include "window/Window.h"


void process_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() 
{
    Window window;
    window.init();

    while(!glfwWindowShouldClose(window.get()))
    {
        process_input(window.get());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window); // Double buffering
        glfwPollEvents();
    }
}