#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DEFAULT_FOV glm::radians(45.f)
#define DEFAULT_POSITION glm::vec3(0.f, 0.f, 3.f)
#define DEFAULT_TRANSLATION_SPEED 2.5f
#define DEFAULT_ROTATION_SPEED 0.2f

namespace egen
{

class Camera
{
public:

    enum Direction
    {
        Up,
        Right,
        Front
    };

    enum Rotation
    {
        Yaw,
        Pitch,
        //Roll
    };

    Camera(float width, float height, float fov = DEFAULT_FOV, glm::vec3 position = DEFAULT_POSITION, float translation_speed = DEFAULT_TRANSLATION_SPEED, float rotation_speed = DEFAULT_ROTATION_SPEED);

    glm::vec3 get_position();

    void set_viewport(float width, float height);
    void set_fov(float fov);
    void set_translation_speed(float translation_speed);
    void set_rotation_speed(float rotation_speed);

    void translate(Direction direction, float value);
    void rotate(Rotation rotation, float value);

    void look_at(glm::vec3 position);

    glm::mat4 compute_mvp(glm::mat4& model);

private:
    void update_projection();
    void update_view();
    void update_direction_vectors();

    glm::mat4 m_view = glm::mat4(1.f);
    glm::mat4 m_projection = glm::mat4(1.f);

    float m_fov;
    float m_width;
    float m_height;

    static constexpr glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;

    float m_yaw;
    float m_pitch;

    float m_translation_speed;
    float m_rotation_speed;
};

}
