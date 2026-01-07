#version 330 core

out vec4 frag_color;

in vec3 frag_pos;
in vec3 normal;

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform float ambient_strength;

void main()
{
    vec3 ambient = ambient_strength * light_color;
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    frag_color = vec4((ambient + diffuse) * object_color, 1.0f);
}