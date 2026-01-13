#include "egen/window/Window.hpp"
#include "egen/renderer/Renderer.hpp"
#include "egen/renderer/primitives/cube.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define WIDTH 800
#define HEIGHT 600

using namespace egen;

void process_key_input(Window& window, Camera& camera, float dt)
{
    if(window.is_key_pressed(Keyboard::Key::Escape))
        window.close();

    if(window.is_key_pressed(Keyboard::Key::A))
        camera.translate(Camera::Direction::Right, -dt);

    if(window.is_key_pressed(Keyboard::Key::D))
        camera.translate(Camera::Direction::Right, dt);

    if(window.is_key_pressed(Keyboard::Key::S))
        camera.translate(Camera::Direction::Front, -dt);

    if(window.is_key_pressed(Keyboard::Key::W))
        camera.translate(Camera::Direction::Front, +dt);
}

static void process_mouse_input(double x, double y, double dx, double dy, Camera& camera, float& dt)
{
    float pitch = dt * dy;
    float yaw = dt * dx;
    
    camera.rotate(Camera::Rotation::Pitch, pitch);
    camera.rotate(Camera::Rotation::Yaw, yaw);
}

void rotate_light(Renderer::Command& light_render_command, Shader& cube_shader, float dt)
{
    float val = 0.7f * dt;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), val, glm::vec3(0.0f, 1.0f, 0.0f));
    light_render_command.model = rotation * light_render_command.model;

    glm::vec3 light_pos = glm::vec3(light_render_command.model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    cube_shader.use();
    cube_shader.set_uniform("light.position", light_pos);
}

std::vector<Renderer::Command> get_render_commands(Shader& cube_shader, Shader& light_shader)
{
    GLuint cube_vao = primitives::cube();

    glm::mat4 model1 = glm::mat4(1.0f);
    glm::mat4 model2 = glm::translate(glm::mat4(1.0f), glm::vec3(1.8f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 model3 = glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.5f, -0.3f)) * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.2f));

    glm::mat4 light_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.0f, 3.0f));
    light_model = glm::scale(light_model, glm::vec3(0.2f));

    glm::vec3 light_pos = glm::vec3(light_model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glm::vec3 light_color(1.f, 1.f, 1.f);

    light_shader.use();
    light_shader.set_uniform("color", light_color);
    cube_shader.use();
    cube_shader.set_uniform("color", glm::vec3(0.8f, 0.6f, 0.3f));
    cube_shader.set_uniform("light.ambient", light_color);
    cube_shader.set_uniform("light.diffuse", light_color);
    cube_shader.set_uniform("light.specular", light_color);
    cube_shader.set_uniform("light.position", light_pos);

    std::vector<Renderer::Command> render_commands = {
        Renderer::Command{
            .vao = cube_vao,
            .index_count = 36,
            .shader = &cube_shader,
            .texture = nullptr,
            .model = model1
        },
        Renderer::Command{
            .vao = cube_vao,
            .index_count = 36,
            .shader = &cube_shader,
            .texture = nullptr,
            .model = model2
        },
        Renderer::Command{
            .vao = cube_vao,
            .index_count = 36,
            .shader = &cube_shader,
            .texture = nullptr,
            .model = model3
        },
        Renderer::Command{
            .vao = cube_vao,
            .index_count = 36,
            .shader = &light_shader,
            .texture = nullptr,
            .model = light_model
        }
    };

    return render_commands;
}

int main(int argc, char* argv[]) 
{
    Window window(WIDTH, HEIGHT);
    window.init();
    Camera camera(WIDTH, HEIGHT);
    Renderer renderer(window, camera);

    std::filesystem::path common_shader_path = "../src/egen/shaders";
    std::filesystem::path cube_vertex_shader_path = "../examples/basic_light/shaders/cube.vert";
    std::filesystem::path cube_fragment_shader_path = "../examples/basic_light/shaders/cube.frag";
    std::filesystem::path light_vertex_shader_path = "../examples/basic_light/shaders/light.vert";
    std::filesystem::path light_fragment_shader_path = "../examples/basic_light/shaders/light.frag";
    Shader cube_shader(common_shader_path, cube_vertex_shader_path, cube_fragment_shader_path);
    Shader light_shader(common_shader_path, light_vertex_shader_path, light_fragment_shader_path);

    float dt = 0.f;
    float last_frame = 0.f;

    window.set_mouse_input_callback([&camera, &dt](float x, float y, float dx, float dy) {
        process_mouse_input(x, y, dx, dy, camera, dt);
    });
    window.set_mouse_anchored(true);

    auto render_commands = get_render_commands(cube_shader, light_shader);

    while(!window.should_close())
    {
        float current_frame = static_cast<float>(glfwGetTime());
        dt = current_frame - last_frame;
        last_frame = current_frame;

        window.handle_events();
        process_key_input(window, camera, dt);

        for(auto& render_command : render_commands)
        {
            renderer.add_render_command(render_command);
        }
        renderer.flush();

        rotate_light(render_commands[render_commands.size()-1], cube_shader, dt);
    }

    return 0;
}