#include "renderer/Renderer.hpp"

#include <iostream>

namespace egen
{

Renderer::Renderer(Window& window) : m_window(window)
{
    
}

void Renderer::add_render_command(Command render_command)
{
    m_render_command_queue.push(render_command);
}

void Renderer::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for(; !m_render_command_queue.empty(); m_render_command_queue.pop())
    {
        auto& render_command = m_render_command_queue.front();
        glUseProgram(render_command.shader->get_shader_program());
        glBindVertexArray(render_command.vao);
        glDrawElements(GL_TRIANGLES, render_command.index_count, GL_UNSIGNED_INT, 0);
    }

    glfwSwapBuffers(m_window.get()); // Double buffering
}

}