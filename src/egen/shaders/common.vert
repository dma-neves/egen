#version 330 core

uniform mat4 model;
uniform mat4 mvp;

mat4 get_mvp()
{
    return mvp;
}

mat4 get_model()
{
    return model;
}

vec3 transform_normal(vec3 normal)
{
    return normalize(mat3(transpose(inverse(model))) * normal); 
}