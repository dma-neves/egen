#version 330 core

mat4 get_mvp();
mat4 get_model();

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

out vec3 frag_pos;
out vec3 normal;

void main()
{
    gl_Position = get_mvp() * vec4(a_pos, 1.0);
    frag_pos = vec3(get_model() * vec4(a_pos, 1.0));
    normal = a_normal;
}