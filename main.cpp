#include <print>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Cube.h"
#include "Shader.h"
#include "Camera.h"

namespace Clone {
    Camera camera{};

    float deltaTime{ 0.0f };
    float lastFrame{ 0.0f };
    float lastX{ 400.0f };
    float lastY{ 300.0f };
    bool firstMouse{ true };

    void error_callback(int32_t error, const char *msg);

    void framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height);
    void mouse_callback(GLFWwindow *window, double xPos, double yPos);
    void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);
    void processInput(GLFWwindow *window);

    void framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height)
    {
        glViewport(0, 0, width, height);
    }

    void processInput(GLFWwindow *window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.ProcessKeyboard(CameraMovement::UP, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            camera.ProcessKeyboard(CameraMovement::DOWN, deltaTime);
    }

    void error_callback(int32_t error, const char *msg)
    {
        std::println(std::cerr, "[{}] {}", error, msg);
    }

    void mouse_callback(GLFWwindow *window, double xPos, double yPos)
    {
        if (firstMouse)
        {
            lastX = xPos;
            lastY = yPos;
            firstMouse = false;
        }

        camera.ProcessMouseMovement(xPos - lastX, lastY - yPos);
        lastX = xPos;
        lastY = yPos;
    }

    void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
    {
        camera.ProcessMouseScroll(yOffset);
    }
}

int main()
{
    constexpr int32_t initWindowWidth{ 800 };
    constexpr int32_t initWindowHeight{ 600 };

    if (!glfwInit())
    {
        std::println(std::cerr, "Failed to init GLFW");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif //__APPLE__

    glfwSetErrorCallback(Clone::error_callback);

    GLFWwindow *window = glfwCreateWindow(initWindowWidth, initWindowHeight, "Minecraft Clone", nullptr, nullptr);

    if (window == nullptr)
    {
        std::println(std::cerr, "Failed creating window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::println(std::cerr, "Failed loading GLAD");
        return -1;
    }

    glViewport(0, 0, initWindowWidth, initWindowHeight);
    glfwSetFramebufferSizeCallback(window, Clone::framebuffer_size_callback);

    Clone::Shader shader{ "./shaders/shader.vert", "./shaders/shader.frag" };

    uint32_t VAO, VBO;
    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Clone::Cube::vertices), Clone::Cube::vertices, GL_STATIC_DRAW);

    uint32_t EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Clone::Cube::indices), Clone::Cube::indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    shader.Use();

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, Clone::mouse_callback);
    glfwSetScrollCallback(window, Clone::scroll_callback);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame{ (float)glfwGetTime() };
        Clone::deltaTime = currentFrame - Clone::lastFrame;
        Clone::lastFrame = currentFrame;

        Clone::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model{ glm::mat4{ 1.0f } };
//        model = glm::translate(model, glm::vec3{ 1.0f, 1.0f, 0.0f });

        glm::mat4 view{ glm::lookAt(Clone::camera.Position, Clone::camera.Position + Clone::camera.Front, Clone::camera.Up) };

        int32_t screenWidth, screenHeight;
        glfwGetWindowSize(window, &screenWidth, &screenHeight);
        glm::mat4 projection{ glm::perspective(glm::radians(Clone::camera.Fov), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f) };

        shader.SetMat4("model", model);
        shader.SetMat4("view", view);
        shader.SetMat4("projection", projection);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
