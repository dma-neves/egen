#include "renderer/Renderer.hpp"

#include <iostream>

namespace egen
{

Renderer::Renderer(Window& window) : m_window(window)
{
    
}


void Renderer::update()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // glUseProgram(shaderProgram);
    // glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(m_window.get()); // Double buffering
}

void Renderer::add_triangle()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};


    glGenVertexArrays(1, &VAO);  // Vertex Array Object: Combines VBO data with Vertex Attributes
    glBindVertexArray(VAO);     // After binding, VAO will store subsequent information/state about glEnableVertexAttribArray, glVertexAttribPointer

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
    // glUseProgram(shaderProgram); // Activate the Shader Program
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader); // After the shaders have been linked to the program, we can delete them

    // These attributes will be associated with the bounded VBO. Attributes tell the shader how to interpret and cosume data from VBO
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

void Renderer::add_rectangle()
{
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
    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader);
    glLinkProgram(shaderProgram2);
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING\n"
                  << infoLog << std::endl;
    }
    glUseProgram(shaderProgram2); // Activate the Shader Program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); // After the shaders have been linked to the program, we can delete them





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

    unsigned int VBO, EBO;
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 


}

}