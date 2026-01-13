#include "egen/window/Window.hpp"
#include "egen/renderer/Renderer.hpp"
#include "egen/renderer/primitives/cube.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 800
#define HEIGHT 600

using namespace egen;

void process_key_input(Window& window, float& angle_x, float& angle_y)
{
    if(window.is_key_pressed(Keyboard::Key::Escape))
        window.close();

    constexpr float angle_increment = 2.0f;

    if(window.is_key_pressed(Keyboard::Key::Left))
        angle_y -= angle_increment;

    if(window.is_key_pressed(Keyboard::Key::Right))
        angle_y += angle_increment;

    if(window.is_key_pressed(Keyboard::Key::Down))
        angle_x += angle_increment;

    if(window.is_key_pressed(Keyboard::Key::Up))
        angle_x -= angle_increment;
}

glm::mat4 compute_model(float angle_x, float angle_y)
{
    glm::mat4 mvp = glm::mat4(1.0f);
    mvp = glm::rotate(mvp, glm::radians(angle_x), glm::vec3(1.0f, 0.0f, 0.0f));
    mvp = glm::rotate(mvp, glm::radians(angle_y), glm::vec3(0.0f, 1.0f, 0.0f));

    return mvp;
}

int main(int argc, char* argv[]) 
{
    float angle_x = 0.0f;
    float angle_y = 0.0f;

    Window window(WIDTH, HEIGHT);
    window.init();
    Camera camera(WIDTH, HEIGHT);
    Renderer renderer(window, camera);

    std::filesystem::path common_shader_path = "../src/egen/shaders";
    std::filesystem::path vertex_shader_path = "../examples/cube/shaders/cube.vert";
    std::filesystem::path fragment_shader_path = "../examples/cube/shaders/cube.frag";
    Shader shader(common_shader_path, vertex_shader_path, fragment_shader_path);
    GLuint cube_vao = primitives::cube();

    Renderer::Command cube_render_command{
        .vao = cube_vao,
        .index_count = 36,
        .shader = &shader,
        .texture = nullptr
    };

    while(!window.should_close())
    {
        window.handle_events();
        process_key_input(window, angle_x, angle_y);

        cube_render_command.model = compute_model(angle_x,  angle_y);
        renderer.add_render_command(cube_render_command);
        renderer.flush();
    }

    return 0;
}