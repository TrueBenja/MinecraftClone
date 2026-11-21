#include <cstdint>
#include <string>
#include <print>
#include <iostream>
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

namespace Clone
{
void framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height);

class Window
{
public:
    Window(int32_t width, int32_t height, std::string title) : m_Width(width), m_Height(height)
    {
        if (!glfwInit())
        {
            std::println(std::cerr, "ERROR: Failed to init GLFW");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif //__APPLE__

        m_Window = glfwCreateWindow(m_Width, m_Height, title.c_str(), nullptr, nullptr);

        if (m_Window == nullptr)
        {
            std::println(std::cerr, "ERROR: Failed to create glfw window.");
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::println(std::cerr, "Failed loading GLAD");
        }

        glViewport(0, 0, m_Width, m_Height);
        glfwSetFramebufferSizeCallback(m_Window, Clone::framebuffer_size_callback);
    }

    ~Window()
    {
    }

    GLFWwindow *GetGLFWWindow()
    {
        return m_Window;
    }

private:
    int32_t m_Width;
    int32_t m_Height;
    GLFWwindow *m_Window;
};

} // namespace Clone
