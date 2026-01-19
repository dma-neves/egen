#version 330 core

mat4 get_mvp();

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_tex_coord;

void main()
{
    gl_Position = get_mvp() * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
}