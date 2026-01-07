#version 330 core

uniform vec3 light_color;
uniform vec3 light_pos;
uniform float ambient_strength;

vec3 phong_light(vec3 frag_pos, vec3 normal)
{
    vec3 ambient = ambient_strength * light_color;
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    return ambient + diffuse;
}