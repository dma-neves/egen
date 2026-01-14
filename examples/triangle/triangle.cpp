#include "egen/window/Window.hpp"
#include "egen/renderer/Renderer.hpp"

using namespace egen;

#define WIDTH 800
#define HEIGHT 600

GLuint get_triangle_vao()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2
    };

    GLuint VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // Unbind VBO
    glBindVertexArray(0);               // Unvind VAO

    return VAO;
}

int main(int argc, char* argv[]) 
{

    Window window(WIDTH, HEIGHT);
    window.init();
    Camera camera(WIDTH, HEIGHT);
    Renderer renderer(window, camera);

    
    std::filesystem::path common_shader_path = "../src/egen/shaders";
    std::filesystem::path vertex_shader_path = "../examples/triangle/shaders/triangle.vert";
    std::filesystem::path fragment_shader_path = "../examples/triangle/shaders/triangle.frag";

    Shader shader(common_shader_path, vertex_shader_path, fragment_shader_path);

    Renderer::Command triangle_render_command{
        .vao = get_triangle_vao(),
        .index_count = 3,
        .shader = &shader,
        .texture = nullptr
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