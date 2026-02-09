const int SOLID = 0;
const int BASIC = 1;
const int MAPPED = 2;

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 view_pos;
uniform Light light;

uniform sampler2D diffuse_texture;
uniform sampler2D specular_texture;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float shininess;
uniform int material_type;

vec3 phong(vec3 frag_pos, vec3 normal, vec2 tex_coord)
{
    vec3 diffuse_ = texture(diffuse_texture, tex_coord).rgb;

    if(material_type == BASIC)
    {
        return  phong_impl(frag_pos, normal, ambient, diffuse_, specular, shininess);
    }
    else if(material_type == MAPPED)
    {
        float specular_ = texture(specular_texture, tex_coord).rgb;
        return phong_impl(frag_pos, normal, ambient, diffuse_, specular_, shininess);
    }
}

vec3 phong(vec3 frag_pos, vec3 normal)
{
    if(material_type == SOLID)
    {
        return phong_impl(frag_pos, normal, ambient, diffuse, specular, shininess);
    }
}

vec3 phong_impl(vec3 frag_pos, vec3 normal, float material_ambient, float material_diffuse, float material_specular, float material_shininess)
{

    vec3 ambient = material_ambient * light.ambient;

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(light.position - frag_pos);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material_diffuse);

    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material_shininess);
    vec3 specular = light.specular * (spec * material_specular);

    return ambient + diffuse + specular;
}

