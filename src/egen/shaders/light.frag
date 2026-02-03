#version 330 core

struct PhongMaterial
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 view_pos;
uniform Light light;

vec3 phong(vec3 frag_pos, vec3 normal, PhongMaterial material)
{
    vec3 ambient = material.ambient * light.ambient;

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light.position - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = light.specular * (spec * material.specular);

    return ambient + diffuse + specular;
}