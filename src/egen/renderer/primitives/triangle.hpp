#pragma once

#include "platform/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace egen
{
    class Triangle
    {
    public:
        static Triangle &get_instance();

        GLuint vao();
        uint32_t index_count();

    private:
        GLuint m_vao;

        void compute_vao();

        static constexpr float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f};
        static constexpr unsigned int indices[] = {
            0, 1, 2};
    };
}
