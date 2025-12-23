#include "renderer/Renderer.hpp"

#include <iostream>

namespace egen::renderer
{

Renderer::Renderer(window::Window& window) : m_window(window)
{
    
}


void Renderer::update()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(m_window.get()); // Double buffering
}

void Renderer::add_triangle()
{
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
    glShaderSource(vertexShader, 1, &m_vertex_shader_source, NULL);
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
    glShaderSource(fragmentShader, 1, &m_fragment_shader_source, NULL);
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

}