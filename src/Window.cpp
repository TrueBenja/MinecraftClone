#include "Window.hpp"
namespace Clone
{
void framebuffer_size_callback(GLFWwindow *window, int32_t width, int32_t height)
{
    glViewport(0, 0, width, height);
}
} // namespace Clone
