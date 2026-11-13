#include "Camera.h"

namespace Clone {
    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
    {
        float velocity{ MovementSpeed * deltaTime };
        if (direction == CameraMovement::FORWARD)
            Position += Front * velocity;
        if (direction == CameraMovement::BACKWARD)
            Position -= Front * velocity;
        if (direction == CameraMovement::LEFT)
            Position -= Right * velocity;
        if (direction == CameraMovement::RIGHT)
            Position += Right * velocity;
        if (direction == CameraMovement::UP)
            Position += WorldUp * velocity;
        if (direction == CameraMovement::DOWN)
            Position -= WorldUp * velocity;
    }

    void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
    {
        xOffset *= MouseSensitivity;
        yOffset *= MouseSensitivity;

        Yaw += xOffset;
        Pitch += yOffset;

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        UpdateCameraVectors();
    }

    void Camera::ProcessMouseScroll(float yOffset)
    {
        Fov -= yOffset;
        if (Fov < 1.0f)
            Fov = 1.0f;
        if (Fov > 45.0f)
            Fov = 45.0f;
    }

    void Camera::UpdateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
}
