#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

uniform mat4 mvp;
uniform mat4 model;

out vec3 vertex_color;
out vec3 frag_pos;
out vec3 normal;

void main()
{
    gl_Position = mvp * vec4(a_pos, 1.0);
    frag_pos = vec3(model * vec4(a_pos, 1.0));
    normal = a_normal;
}