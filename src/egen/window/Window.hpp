#pragma once

#include "platform/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <stdexcept>

namespace egen
{

class Window 
{
public:

    Window(float width, float heigh);

    int init();
    void terminate();
    GLFWwindow* get();

    void set_key_input_callback(std::function<void(GLFWwindow* window)> key_input_callback);
    void set_mouse_input_callback(std::function<void(GLFWwindow* window, float x, float y, float dx, float dy)> mouse_input_callback);
    void set_mouse_anchored(bool anchored);

    bool should_close();
    void handle_events();

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void center_mouse();

    GLFWwindow *m_window;
    float m_width;
    float m_height;
    std::function<void(GLFWwindow* window)> m_key_input_callback;
    std::function<void(GLFWwindow* window, float x, float y, float dx, float dy)> m_mouse_input_callback;

    float m_mouse_x;
    float m_mouse_y;
    bool m_reset_mouse_delta = true;
    bool m_mouse_anchored = false;
    bool m_focused = true;
};

}
