#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>

void hndKbInput(GLFWwindow *wnd, int &scene, float &time0)
{
    if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(wnd, true);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_0) == GLFW_PRESS)
    {
        scene = 0;
    }
    else if (glfwGetKey(wnd, GLFW_KEY_1) == GLFW_PRESS)
    {
        scene = 1;
    }
    else if (glfwGetKey(wnd, GLFW_KEY_T) == GLFW_PRESS)
    {
        time0 = glfwGetTime();
    }
}