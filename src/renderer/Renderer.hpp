#pragma once

#include "window/Window.hpp"
#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <queue>

namespace egen
{

class Renderer
{
public:
    struct Command
    {
        uint32_t vao;
        uint32_t index_count;
        Shader* shader;
        Texture* texture;
        glm::mat4 mvp{1.0f};
    };

    Renderer(Window& window);

    void add_render_command(Command render_command);
    void flush();

private:
    Window& m_window;
    std::queue<Command> m_render_command_queue;

};

}