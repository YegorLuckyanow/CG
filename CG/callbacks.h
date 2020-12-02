#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

void fbSzCallback(GLFWwindow *wnd, int w, int h);
void hndKbInput(GLFWwindow *wnd, glm::vec3 &cameraUp);