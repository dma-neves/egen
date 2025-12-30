#pragma once

#include "egen/window/Window.hpp"
#include "egen/renderer/Shader.hpp"
#include "egen/renderer/Texture.hpp"
#include "egen/renderer/Camera.hpp"

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
        glm::mat4 model{1.0f};
    };

    Renderer(Window& window, Camera& camera);

    void add_render_command(Command render_command);
    void flush();

private:
    Window& m_window;
    Camera& m_camera;
    std::queue<Command> m_render_command_queue;

};

}
