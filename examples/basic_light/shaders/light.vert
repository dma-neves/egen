#version 330 core

layout (location = 0) in vec3 a_pos;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
}