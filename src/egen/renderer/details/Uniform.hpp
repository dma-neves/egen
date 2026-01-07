#pragma once

#include "platform/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <type_traits>


namespace egen::details
{

template<class> inline constexpr bool always_false = false;

template <typename T>
void set_uniform(const GLint& loc, const T& value)
{
    if constexpr (std::is_same_v<T, float>)
    {
        glUniform1f(loc, value);
    }
    else if constexpr (std::is_same_v<T, int>)
    {
        glUniform1i(loc, value);
    } 
    else if constexpr (std::is_same_v<T, glm::vec3>)
    {
        glUniform3fv(loc, 1, glm::value_ptr(value));
    } 
    else if constexpr (std::is_same_v<T, glm::mat4>)
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    } 
    else
    {
        static_assert(always_false<T>, "Unsupported uniform type in Shader::set_uniform");
    }
}

}