#include "egen/window/Window.hpp"
#include "egen/renderer/Renderer.hpp"
#include "cube_data.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH 800
#define HEIGHT 600

using namespace egen;

static void process_key_input(GLFWwindow *window, Camera& camera, float dt)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_A))
        camera.translate(Camera::Direction::Right, -dt);

    if(glfwGetKey(window, GLFW_KEY_D))
        camera.translate(Camera::Direction::Right, dt);

    if(glfwGetKey(window, GLFW_KEY_S))
        camera.translate(Camera::Direction::Front, -dt);

    if(glfwGetKey(window, GLFW_KEY_W))
        camera.translate(Camera::Direction::Front, +dt);
}

static void process_mouse_input(GLFWwindow *window,  double x, double y, double dx, double dy, Camera& camera, float& dt)
{
    float pitch = dt * dy;
    float yaw = dt * dx;
    
    camera.rotate(Camera::Rotation::Pitch, pitch);
    camera.rotate(Camera::Rotation::Yaw, yaw);
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
    Window window(WIDTH, HEIGHT);
    window.init();
    Camera camera(WIDTH, HEIGHT);
    Renderer renderer(window, camera);

    float dt = 0.f;
    float last_frame = 0.f;

    window.set_key_input_callback([&camera, &dt](GLFWwindow* window) {
        process_key_input(window, camera, dt);
    });

    window.set_mouse_input_callback([&camera, &dt](GLFWwindow* window, float x, float y, float dx, float dy) {
        process_mouse_input(window, x, y, dx, dy, camera, dt);
    });

    window.set_mouse_anchored(true);

    std::filesystem::path vertex_shader_path = "../examples/cube/shaders/cube.vert";
    std::filesystem::path fragment_shader_path = "../examples/cube/shaders/cube.frag";
    Shader shader(vertex_shader_path, fragment_shader_path);
    GLuint VAO = get_cube_vao();

    Renderer::Command cube_render_command{
        .vao = VAO,
        .index_count = 36,
        .shader = &shader,
        .texture = nullptr,
        .model = glm::mat4(1.f)
    };


    while(!window.should_close())
    {
        float current_frame = static_cast<float>(glfwGetTime());
        dt = current_frame - last_frame;
        last_frame = current_frame;

        window.handle_events();

        renderer.add_render_command(cube_render_command);
        renderer.flush();
    }

    return 0;
}