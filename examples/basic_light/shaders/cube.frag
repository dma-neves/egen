#version 330 core

out vec4 frag_color;

in vec3 vertex_color;

uniform vec3 light_color;

void main()
{
    frag_color = vec4(light_color * vertex_color, 1.0f);
}