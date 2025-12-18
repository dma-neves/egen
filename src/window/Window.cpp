#include "Window.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);
}

void Window::init()
{
    // OpenGL is operating system agnostic. In order to obtain a window and context to draw to, we'll use GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Telling GLFW we want to use the core-profile means we'll get access to a smaller subset of OpenGL features without backwards-compatible features we no longer need.
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // used for mac os

    window = glfwCreateWindow(800, 600, "Learn OpenGl", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Since there are many different versions of OpenGL drivers, the location of most of its functions is not known at compile-time and needs to be queried at run-time.
    // GLAD solves this for us
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600); // viewport is used to transform Normalized Device Coordinates (NDC) to screen coordinates

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Callback for change in window size

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    unsigned int VBO;
    glGenBuffers(1, &VBO);                                                     // Vertex Buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                        // Bind VBO to GL Array Buffer so that all consequent operations are over VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy vertices to GL Array Buffer (which right now is bounded to VBO)
    /*
        Three types of data management:
            - GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
            - GL_STATIC_DRAW: the data is set only once and used many times.
            - GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    */

    // Compile Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Compile Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    // Create Shader Program, attach previous shaders, and link the shaders
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING\n"
                  << infoLog << std::endl;
    }
    glUseProgram(shaderProgram); // Activate the Shader Program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); // After the shaders have been linked to the program, we can delete them

    // These attributes will be associated with the bounded VBO
    glVertexAttribPointer(
        0,                 // Vertex Attribute location (0 is aPos)
        3,                 // Size of vertex attribute
        GL_FLOAT,          // Data Type
        GL_FALSE,          // Data Normalized (to be in range 0-1)
        3 * sizeof(float), // Stride - space between consecutive attributes
        (void *)0          // Offset
    );
    glEnableVertexAttribArray(0);
}

void Window::terminate()
{
    glfwTerminate();
}

GLFWwindow Window::get()
{
    return window;
}