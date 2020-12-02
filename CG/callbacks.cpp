#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>

void fbSzCallback(GLFWwindow *wnd, int w, int h)
{
    glViewport(0, 0, w, h);
}

void hndKbInput(GLFWwindow *wnd, glm::vec3 &cameraUp)
{
    if (glfwGetKey(wnd, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(wnd, true);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_UP) == GLFW_PRESS)
    {
        cameraUp.z += 1;
    }
    else if (glfwGetKey(wnd, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        cameraUp.z -= 1;
    }
    else if (glfwGetKey(wnd, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        cameraUp.x += 1;
    }
    else if (glfwGetKey(wnd, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        cameraUp.x -= 1;
    }
}