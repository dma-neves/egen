#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;

uniform mat4 mvp;

out vec3 vertex_color;

void main()
{
    gl_Position = mvp * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
    vertex_color = a_color;
}