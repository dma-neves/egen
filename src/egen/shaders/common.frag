#version 330 core

uniform vec3 color;

uniform sampler2D tex_sampler;

vec3 get_color()
{
    return color;
}

vec4 get_tex_color(in vec2 tex_coord)
{
    return texture(tex_sampler, tex_coord);
}