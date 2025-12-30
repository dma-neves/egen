#include "egen/window/Window.hpp"

namespace egen
{

Window::Window(std::function<void(GLFWwindow *window)> key_input_callback) : m_key_input_callback(key_input_callback)
{
}

void Window::framebuffer_size_callback(GLFWwindow* m_window, int width, int height) {

    glViewport(0, 0, width, height);
}

int Window::init()
{
    // OpenGL is operating system agnostic. In order to obtain a m_window and context to draw to, we'll use GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Telling GLFW we want to use the core-profile means we'll get access to a smaller subset of OpenGL features without backwards-compatible features we no longer need.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // used for mac os

    m_window = glfwCreateWindow(800, 600, "Learn OpenGl", NULL, NULL);

    if (m_window == NULL)
    {
        throw std::runtime_error("Failed to create GLFW m_window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_window);

    // Since there are many different versions of OpenGL drivers, the location of most of its functions is not known at compile-time and needs to be queried at run-time.
    // GLAD solves this for us
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
        return -1;
    }

    glViewport(0, 0, 800, 600); // viewport is used to transform Normalized Device Coordinates (NDC) to screen coordinates

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback); // Callback for change in m_window size

    glEnable(GL_DEPTH_TEST); // Enable depth testing

    return 0;
}

void Window::terminate()
{
    glfwTerminate();
}

GLFWwindow* Window::get()
{
    return m_window;
}

bool Window::should_close()
{
    return glfwWindowShouldClose(m_window);
}

void Window::process_inputs()
{
    m_key_input_callback(m_window);
}


}
