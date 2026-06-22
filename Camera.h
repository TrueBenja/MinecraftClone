#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Clone {
    enum class CameraMovement
    {
        FORWARD = 0,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    constexpr float YAW{ -90.0f };
    constexpr float PITCH{ 0.0f };
    constexpr float SPEED{ 2.5f };
    constexpr float SENSITIVITY{ 0.1f };
    constexpr float FOV{ 45.0f };

    class Camera
    {
    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        float Yaw;
        float Pitch;

        float MovementSpeed;
        float MouseSensitivity;
        float Fov;

        Camera(glm::vec3 position = glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3 up = glm::vec3{ 0.0f, 1.0f, 0.0f }, float yaw = YAW, float pitch = PITCH)
            : Front(glm::vec3{ 0.0f, 0.0f, -1.0f }), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV), Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch)
        {
            UpdateCameraVectors();
        }

        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
            : Front(glm::vec3{ 0.0f, 0.0f, -1.0f }), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Fov(FOV), Position(glm::vec3{ posX, posY, posZ }), WorldUp(glm::vec3{ upX, upY, upZ }), Yaw(yaw), Pitch(pitch)
        {
            UpdateCameraVectors();
        }

        glm::mat4 GetViewMatrix() const;
        void ProcessKeyboard(CameraMovement direction, float deltaTime);
        void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
        void ProcessMouseScroll(float yOffset);

    private:
        void UpdateCameraVectors();
    };
}

#endif //CAMERA_H
