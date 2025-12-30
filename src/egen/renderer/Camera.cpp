#include "egen/renderer/Camera.hpp"

namespace egen
{

Camera::Camera(float width, float height, float fov, glm::vec3 position, float translation_speed, float rotation_speed) : 
    m_width(width),
    m_height(height),
    m_fov(fov),
    m_position(position),
    m_translation_speed(translation_speed),
    m_rotation_speed(rotation_speed)
{
    m_up = world_up;
    m_yaw = glm::radians(-90.0f);
    m_pitch = 0.f;

    update_direction_vectors();
    update_projection();
    update_view();
}

void Camera::set_viewport(float width, float height)
{
    m_width = width;
    m_height = height;
    update_projection();
}

void Camera::set_fov(float fov)
{
    m_fov = fov;
    update_projection();
}

void Camera::set_translation_speed(float translation_speed)
{
    m_translation_speed = translation_speed;
}

void Camera::set_rotation_speed(float rotation_speed)
{
    m_rotation_speed = rotation_speed;
}

void Camera::update_projection()
{
    m_projection = glm::perspective(m_fov, m_width/m_height, 0.1f, 100.0f);
}

void Camera::update_view()
{
    m_view = glm::lookAt(m_position, m_position + m_front, m_up);
}

// Updates front, right, up based on pitch and yaw
void Camera::update_direction_vectors()
{
    m_front = glm::vec3(
        cos(m_yaw) * cos(m_pitch),
        sin(m_pitch),
        sin(m_yaw) * cos(m_pitch)
    ); 
    m_right = glm::cross(m_front, world_up);
    m_up = glm::cross(m_right, m_front);

    m_front = glm::normalize(m_front);
    m_right = glm::normalize(m_right);
    m_up = glm::normalize(m_up);
}

glm::mat4 Camera::compute_mvp(glm::mat4 &model)
{
    return m_projection * m_view * model;
}

void Camera::translate(Direction direction, float value)
{
    switch (direction)
    {
    case Direction::Front:
        m_position += value * m_translation_speed * m_front;
        break;
    case Direction::Right:
        m_position += value * m_translation_speed * m_right;
        break;
    case Direction::Up:
        m_position += value * m_translation_speed * m_up;
        break;
    }

    update_view();
}

void Camera::rotate(Rotation rotation, float value)
{
    switch (rotation)
    {
    case Rotation::Pitch:
        m_pitch += value * m_rotation_speed;
        break;
    case Rotation::Yaw:
        m_yaw += value * m_rotation_speed;
        break;
    }

    update_direction_vectors();
    update_view();
}

void Camera::look_at(glm::vec3 position)
{
    // TODO
}


}


