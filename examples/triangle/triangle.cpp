#include "window/Window.hpp"
#include "renderer/Renderer.hpp"

using namespace egen::window;
using namespace egen::renderer;

void process_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() 
{
    Window window;
    window.init();
    Renderer renderer(window);

    renderer.add_triangle();

    while(!glfwWindowShouldClose(window.get()))
    {
        process_input(window.get());

        renderer.update();

        glfwPollEvents();
    }

    return 0;
}