#include "egen/window/Window.hpp"
#include "egen/renderer/Renderer.hpp"
#include "egen/filesystem/VFS.hpp"
#include "egen/renderer/primitives/triangle.hpp"

using namespace egen;

#define WIDTH 800
#define HEIGHT 600

int main(int argc, char* argv[]) 
{

    Window window(WIDTH, HEIGHT);
    window.init();
    Camera camera(WIDTH, HEIGHT);
    Renderer renderer(window, camera);

    VFS vfs;
    vfs.mount("user-shaders", "../examples/triangle/shaders/");
    std::string vertex_shader_path = "user-shaders://triangle.vert";
    std::string fragment_shader_path = "user-shaders://triangle.frag";
    Shader shader(NONE_COMMON_SHADER, vfs, vertex_shader_path, fragment_shader_path);
    auto& triangle = Triangle::get_instance();

    Renderer::Command triangle_render_command{
        .vao = triangle.vao(),
        .index_count = triangle.index_count(),
        .shader = &shader,
        .material = nullptr
    };

    while(!window.should_close())
    {
        if(window.is_key_pressed(Keyboard::Escape))
            window.close();
            
        window.handle_events();

        renderer.add_render_command(triangle_render_command);
        renderer.flush();
    }

    window.terminate();
    return 0;
}