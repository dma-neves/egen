#include "egen/renderer/Renderer.hpp"

namespace egen
{

Renderer::Renderer(Window& window, Camera& camera) : m_window(window), m_camera(camera)
{
    
}

void Renderer::add_render_command(Command render_command)
{
    m_render_command_queue.push(render_command);
}

void Renderer::flush()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(; !m_render_command_queue.empty(); m_render_command_queue.pop())
    {
        auto& render_command = m_render_command_queue.front();
        glm::mat4 mvp = m_camera.compute_mvp(render_command.model);

        render_command.shader->use();
        render_command.shader->set_uniform("mvp", mvp);
        render_command.shader->set_uniform("model", render_command.model);
        render_command.shader->set_uniform("view_pos", m_camera.get_position());
        glBindVertexArray(render_command.vao);
        glDrawElements(GL_TRIANGLES, render_command.index_count, GL_UNSIGNED_INT, 0);
    }

    glfwSwapBuffers(m_window.get()); // Double buffering
}

}
