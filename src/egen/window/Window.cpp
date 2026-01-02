#include "egen/window/Window.hpp"

namespace egen
{

Window::Window(float width, float height) : m_width(width), m_height(height)
{
}

void Window::framebuffer_size_callback(GLFWwindow* m_window, int width, int height) 
{
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

    m_window = glfwCreateWindow(m_width, m_height, "egen", NULL, NULL);

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

    glViewport(0, 0, m_width, m_height); // viewport is used to transform Normalized Device Coordinates (NDC) to screen coordinates

    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback); // Callback for change in m_window size

    glEnable(GL_DEPTH_TEST); // Enable depth testing

    glfwSetWindowUserPointer(m_window, this); // Bind this pointer to window user pointer

    glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focused) { // Callback when window comes to focus
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        if (focused)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            self->m_reset_mouse_delta = true;
            self->m_focused = true;
        }
        else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            self->m_focused = false;
        }
    });

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


void Window::set_key_input_callback(std::function<void(GLFWwindow*)> key_input_callback)
{
    m_key_input_callback = key_input_callback;
}

void Window::set_mouse_input_callback(std::function<void(GLFWwindow* window, float x, float y, float dx, float dy)> mouse_input_callback)
{
    m_mouse_input_callback = mouse_input_callback;

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* w, double x, double y) {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(w));
        if (self->m_focused)
        {
            float dx ,dy;
            if(self->m_reset_mouse_delta)
            {
                dx = 0.f;
                dy = 0.f;
                self->m_reset_mouse_delta = false;
            }
            else 
            {
                dx = x - self->m_mouse_x;
                dy = -(y - self->m_mouse_y);
            }

            self->m_mouse_x = x;
            self->m_mouse_y = y;

            if(self->m_mouse_input_callback)
            {
                self->m_mouse_input_callback(w, x, y, dx, dy);
            }
        }
    });
}

void Window::set_mouse_anchored(bool anchored)
{
    m_mouse_anchored = anchored;
}

bool Window::should_close()
{
    return glfwWindowShouldClose(m_window);
}

void Window::handle_events()
{
    glfwPollEvents();
    m_key_input_callback(m_window);

    if(m_mouse_anchored)
    {
        center_mouse();
    }
}

void Window::center_mouse()
{
    glfwSetCursorPos(m_window, m_width / 2.0, m_height / 2.0);
    m_mouse_x = m_width / 2.0;
    m_mouse_y = m_height / 2.0;
}


}
