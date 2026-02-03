#include "egen/renderer/primitives/triangle.hpp"

namespace egen
{

Triangle& Triangle::get_instance()
{
    static Triangle instance;
    instance.compute_vao();
    return instance;
}

GLuint Triangle::vao()
{
    return m_vao;
}

uint32_t Triangle::index_count()
{
    return 3;
}

void Triangle::compute_vao()
{
    GLuint VBO, EBO;
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_vao);

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
