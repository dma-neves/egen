#version 330 core

vec3 get_color();

out vec4 frag_color;

void main()
{
    frag_color = vec4(get_color(), 1.f);
}