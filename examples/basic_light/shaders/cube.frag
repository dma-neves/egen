#version 330 core

vec3 phong(vec3 frag_pos, vec3 normal, vec2 tex_coord);

in vec3 frag_pos;
in vec3 normal;
in vec2 tex_coord;

out vec4 frag_color;

void main()
{
    frag_color = vec4(phong(frag_pos, normal, tex_coord), 1.0f);
}