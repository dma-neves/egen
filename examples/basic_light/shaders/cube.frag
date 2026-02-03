#version 330 core

struct PhongMaterial
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

vec3 phong(vec3 frag_pos, vec3 normal, PhongMaterial material);

in vec3 frag_pos;
in vec3 normal;
in vec2 tex_coord;

uniform sampler2D diffuse;
uniform sampler2D specular;
uniform float shininess;

out vec4 frag_color;

void main()
{
    PhongMaterial material;
    material.ambient = texture(diffuse, tex_coord).rgb * 0.1f;
    material.diffuse = texture(diffuse, tex_coord).rgb;
    material.specular = texture(specular, tex_coord).rgb;
    material.shininess = shininess;
    frag_color = vec4(phong(frag_pos, normal, material), 1.0f);
}