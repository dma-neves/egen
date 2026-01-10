#pragma once

static float light_vertices[] = {
        // front
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        // top
        -0.5f, 0.5f, -0.5f, 
        0.5f, 0.5f, -0.5f, 
        0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f, 
        // left
        -0.5f, -0.5f, -0.5f, 
        -0.5f, 0.5f, -0.5f, 
        -0.5f, 0.5f, 0.5f, 
        -0.5f, -0.5f, 0.5f, 
        // right
        0.5f, -0.5f, -0.5f, 
        0.5f, 0.5f, -0.5f, 
        0.5f, 0.5f, 0.5f, 
        0.5f, -0.5f, 0.5f, 
        // back
        -0.5f, -0.5f, 0.5f, 
        0.5f, -0.5f, 0.5f, 
        0.5f, 0.5f, 0.5f, 
        -0.5f, 0.5f, 0.5f, 
        // bottom
        -0.5f, -0.5f, 0.5f, 
        0.5f, -0.5f, 0.5f, 
        0.5f, -0.5f, -0.5f, 
        -0.5f, -0.5f, -0.5f
};

static unsigned int light_indices[] =  {
    // front
    0, 1, 2, // first triangle
    2, 3, 0, // second triangle

    // top
    4, 5, 6, // first triangle
    6, 7, 4, // second triangle

    // left
    8, 9, 10,  // first triangle
    10, 11, 8, // second triangle

    // right
    14, 13, 12, // 12, 13, 14, // first triangle
    12, 15, 14, // 14, 15, 12, // second triangle

    // back
    18, 17, 16, // 16, 17, 18, // first triangle
    16, 19, 18, // 18, 19, 16, // second triangle

    // bottom
    20, 21, 22, // first triangle
    22, 23, 20  // second triangle
};

GLuint get_light_vao()
{
    GLuint VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(light_vertices), light_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(light_indices), light_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // Unbind VBO
    glBindVertexArray(0);               // Unbind VAO

    return VAO;
}