#version 330 core

vec3 phong_light(vec3 frag_pos, vec3 normal);
vec3 get_color();

out vec4 frag_color;

in vec3 frag_pos;
in vec3 normal;

void main()
{
    frag_color = vec4(phong_light(frag_pos, normal) * get_color(), 1.0f);
}