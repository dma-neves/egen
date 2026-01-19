#version 330 core

vec3 phong_light(vec3 frag_pos, vec3 normal);
vec3 get_color();
vec4 get_tex_color(in vec2 tex_coord);

out vec4 frag_color;

in vec3 frag_pos;
in vec3 normal;
in vec2 tex_coord;

void main()
{
    vec3 tex_color = get_tex_color(tex_coord).rgb;
    frag_color = vec4(phong_light(frag_pos, normal) * tex_color, 1.0f);
}