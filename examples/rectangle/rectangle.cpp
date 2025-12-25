#include "window/Window.hpp"
#include "renderer/Renderer.hpp"

using namespace egen;

void process_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLuint get_rectangle_vao()
{
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
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
    glBindVertexArray(0);               // Unbind VAO

    return VAO;
}

int main(int argc, char* argv[]) 
{
    Window window;
    window.init();
    Renderer renderer(window);

    std::filesystem::path vertex_shader_path = "../examples/rectangle/shaders/rectangle.vert";
    std::filesystem::path fragment_shader_path = "../examples/rectangle/shaders/rectangle.frag";

    Shader shader(vertex_shader_path, fragment_shader_path);

    Renderer::Command rectangle_render_command{
        .vao = get_rectangle_vao(),
        .index_count = 6,
        .shader = &shader,
        .texture = nullptr
    };

    while(!glfwWindowShouldClose(window.get()))
    {
        process_input(window.get());

        renderer.add_render_command(rectangle_render_command);
        renderer.render();

        glfwPollEvents();
    }

    return 0;
}