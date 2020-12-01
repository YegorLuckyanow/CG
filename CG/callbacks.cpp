#include <glad/glad.h>
#include <GLFW/glfw3.h>

void fbSzCallback(GLFWwindow *wnd, int w, int h)
{
    glViewport(0, 0, w, h);
}

void hndKbInput(GLFWwindow *wnd)
{
    if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(wnd, true);
    }
}