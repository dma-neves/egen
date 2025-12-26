#include "window/Window.hpp"
#include "renderer/Renderer.hpp"
#include "cube_data.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace egen;

static void process_input(GLFWwindow *window, float& angle_x, float& angle_y)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    constexpr float angle_increment = 2.0f;

    if(glfwGetKey(window, GLFW_KEY_LEFT))
        angle_y -= angle_increment;

    if(glfwGetKey(window, GLFW_KEY_RIGHT))
        angle_y += angle_increment;

    if(glfwGetKey(window, GLFW_KEY_DOWN))
        angle_x -= angle_increment;

    if(glfwGetKey(window, GLFW_KEY_UP))
        angle_x += angle_increment;
}

GLuint get_cube_vao()
{
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // Unbind VBO
    glBindVertexArray(0);               // Unbind VAO

    return VAO;
}

int main(int argc, char* argv[]) 
{
    float angle_x = 0.0f;
    float angle_y = 0.0f;

    auto key_input_callback = [&angle_x, &angle_y](GLFWwindow* window) {
        process_input(window, angle_x, angle_y);
    };

    Window window(key_input_callback);
    window.init();
    Renderer renderer(window);

    std::filesystem::path vertex_shader_path = "../examples/cube/shaders/cube.vert";
    std::filesystem::path fragment_shader_path = "../examples/cube/shaders/cube.frag";
    Shader shader(vertex_shader_path, fragment_shader_path);
    GLuint VAO = get_cube_vao();

    Renderer::Command cube_render_command{
        .vao = VAO,
        .index_count = 36,
        .shader = &shader,
        .texture = nullptr
    };

    while(!window.should_close())
    {
        window.process_inputs();

        auto model_matrix = glm::mat4(1.0f);
        model_matrix = glm::rotate(model_matrix, glm::radians(angle_x), glm::vec3(1.0f, 0.0f, 0.0f));
        model_matrix = glm::rotate(model_matrix, glm::radians(angle_y), glm::vec3(0.0f, 1.0f, 0.0f));

        auto model_matrix_location = glGetUniformLocation(shader.get_shader_program(), "model_matrix");
        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(model_matrix));

        renderer.add_render_command(cube_render_command);
        renderer.render();

        glfwPollEvents();
    }

    return 0;
}