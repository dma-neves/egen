#version 330 core

uniform vec3 light_color;
uniform vec3 light_pos;
uniform float ambient_strength;
uniform float specular_strength;
uniform float specular_shininess;
uniform vec3 view_pos;

vec3 phong_light(vec3 frag_pos, vec3 normal)
{
    vec3 ambient = ambient_strength * light_color;

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * light_color;

    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = specular_strength * spec * light_color;  

    return ambient + diffuse + specular;
}