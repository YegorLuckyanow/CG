#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include <windows.h>

void hndKbInput(GLFWwindow *wnd, int &scene, float &time0, int &neg, float &smokeInt)
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
        Sleep(100);
        //while (glfwGetKey(wnd, GLFW_KEY_T) == GLFW_PRESS);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_N) == GLFW_PRESS)
    {
        neg = (neg == 0) ? 1 : 0;
        Sleep(100);
        //while (glfwGetKey(wnd, GLFW_KEY_N) == GLFW_PRESS);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_UP) == GLFW_PRESS)
    {
        smokeInt -= 1.0f;
        if (smokeInt < 0)
        {
            smokeInt = 0;
        }
        Sleep(100);
    }
    else if (glfwGetKey(wnd, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        smokeInt += 1.0f;
        Sleep(100);
    }
}