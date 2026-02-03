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

void rotate_lantern(Renderer::Command& lantern_render_command, Shader& cube_shader, float dt)
{
    float val = 0.7f * dt;
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), val, glm::vec3(0.0f, 1.0f, 0.0f));
    lantern_render_command.model = rotation * lantern_render_command.model;

    glm::vec3 lantern_pos = glm::vec3(lantern_render_command.model * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    cube_shader.use();
    cube_shader.set_uniform("light.position", lantern_pos);
}

std::vector<Renderer::Command> get_render_commands(Shader& cube_shader, Shader& lantern_shader, Material& container_material)
{
    std::vector<glm::mat4> models = {
        glm::mat4(1.0f),
        glm::translate(glm::mat4(1.0f), glm::vec3(1.8f, 0.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
        glm::translate(glm::mat4(1.0f), glm::vec3(-1.5f, 0.5f, -0.3f)) * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.2f)),
        glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.0f, 3.0f)),  glm::vec3(0.2f))
    };

    constexpr uint16_t lantern_model_index = 3;
    glm::vec3 lantern_pos = glm::vec3(models[lantern_model_index] * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glm::vec3 lantern_color(1.f, 1.f, 1.f);
    glm::vec3 cube_color(0.8f, 0.6f, 0.3f);

    lantern_shader.use();
    lantern_shader.set_uniform("color", lantern_color);
    cube_shader.use();
    cube_shader.set_uniform("color", cube_color);
    cube_shader.set_uniform("light.ambient", lantern_color);
    cube_shader.set_uniform("light.diffuse", lantern_color);
    cube_shader.set_uniform("light.specular", lantern_color);
    cube_shader.set_uniform("light.position", lantern_pos);

    auto& cube = Cube::get_instance();

    std::vector<Renderer::Command> render_commands; 
    for(uint16_t i = 0; i < models.size(); i++)
    {
        render_commands.emplace_back(Renderer::Command{
            .vao = cube.vao(),
            .index_count = cube.index_count(),
            .shader = (i == lantern_model_index) ? &lantern_shader : &cube_shader,
            .material = (i == lantern_model_index) ? nullptr : &container_material,
            .model = models[i]
        });
    }

    return render_commands;
}

int main(int argc, char* argv[]) 
{
    Window window(WIDTH, HEIGHT);
    window.init();
    Camera camera(WIDTH, HEIGHT);
    Renderer renderer(window, camera);

    VFS vfs;
    vfs.mount("common-shaders", "../src/egen/shaders/");
    vfs.mount("user-shaders", "../examples/basic_light/shaders/");
    vfs.mount("assets", "../examples/basic_light/textures/");
    
    std::string cube_vertex_shader_path = "user-shaders://cube.vert";
    std::string cube_fragment_shader_path = "user-shaders://cube.frag";
    std::string lantern_vertex_shader_path = "user-shaders://lantern.vert";
    std::string lantern_fragment_shader_path = "user-shaders://lantern.frag";

    Shader cube_shader(MVP_VERT | LIGHT_FRAG, vfs, cube_vertex_shader_path, cube_fragment_shader_path);
    Shader lantern_shader(MVP_VERT, vfs, lantern_vertex_shader_path, lantern_fragment_shader_path);

    std::string container_texture_path = "assets://container.png";
    std::string container_specular_texture_path = "assets://container_specular.png";
    Texture container_texture(vfs, container_texture_path);
    Texture container_specular_texture(vfs, container_specular_texture_path);

    Material container_material {
        .diffuse = &container_texture,
        .specular = &container_specular_texture,
        .shininess = 32.f
    };

    // TODO: How to avoid setting the texture unit ids here (since they are hardcoded in renderer)
    cube_shader.use();
    cube_shader.set_uniform("diffuse", 0);
    cube_shader.set_uniform("specular", 1);

    float dt = 0.f;
    float last_frame = 0.f;

    window.set_mouse_input_callback([&camera, &dt](float x, float y, float dx, float dy) {
        process_mouse_input(x, y, dx, dy, camera, dt);
    });
    window.set_mouse_anchored(true);

    auto render_commands = get_render_commands(cube_shader, lantern_shader, container_material);

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

        rotate_lantern(render_commands[render_commands.size()-1], cube_shader, dt);
    }

    window.terminate();
    return 0;
}