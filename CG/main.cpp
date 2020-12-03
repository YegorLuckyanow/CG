#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"shader.h"
#include"callbacks.h"
#include"figures.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

int scene = 0;

float wHeight = 600, wWidth = 800;
void fbSzCallback(GLFWwindow *wnd, int w, int h)
{
    glViewport(0, 0, w, h);
    wWidth = w;
    wHeight = h;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, wWidth, wHeight);
    glfwSetFramebufferSizeCallback(window, fbSzCallback);
    Shader prog("vShader.glsl", "fShader.glsl");
    Shader lightprog("vShader.glsl", "lightfShader.glsl");
    /*float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };*/
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    float *vertices = new float[36 * 9 * 10 + 3 * 9];
    for (int i = 1; i < 10; ++i)
    {
        float mult = 0.25f;
        glm::vec3 ang = 0.5f * i * glm::vec3(i % 3 == 1 ? -1.0f : 1.0f, i % 2 == 0 ? -1.0f : 1.0f, i % 3 == 2 ? -1.0f : 1.0f);
        getCube(glm::vec3(i * mult, 0.0f, 0.0f) + ang, glm::vec3(0.0f, -0.0f, -0.0f) + ang, glm::vec3(-0.0f, i * mult, -0.0f) + ang, glm::vec3(0.0f, 0.0f, i * mult) + ang, glm::vec3(0.0, 1.0, 1.0), vertices + i * 36 * 9);
    }
    getTriangle(glm::vec3(-1000.0, -11.0, -1000.0), glm::vec3(-1000.0, -11.0, 1000.0), glm::vec3(1000.0, -11.0, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), vertices + 36 * 9 * 10);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (10 * 36 * 9 + 3 * 9) * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarg = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), wWidth / wHeight, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        hndKbInput(window, cameraUp);
        if (scene == 0)
        {
            projection = glm::perspective(glm::radians(45.0f), wWidth / wHeight, 0.1f, 100.0f);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            glm::vec3 lightPos = glm::vec3(cos(glfwGetTime()) * 1.0f, sin(glfwGetTime()) * 1.0f, -1.0f);
            getCube(glm::vec3(0.1f, 0.0f, 0.0f) + lightPos, lightPos, glm::vec3(-0.0f, 0.1f, -0.0f) + lightPos, glm::vec3(0.0f, 0.0f, 0.1f) + lightPos, lightColor, vertices);
            glBufferData(GL_ARRAY_BUFFER, (10 * 36 * 9 + 3 * 9) * sizeof(float), vertices, GL_STATIC_DRAW);
            cameraPos = glm::vec3(sin(glfwGetTime()) * 20.0f, 0.0f, cos(glfwGetTime()) * 20.0f);
            view = glm::lookAt(cameraPos, cameraTarg, cameraUp);
            lightprog.use();
            lightprog.setMat4("modelMatrix", model);
            lightprog.setMat4("viewMatrix", view);
            lightprog.setMat4("projectionMatrix", projection);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            prog.use();
            prog.setMat4("modelMatrix", model);
            prog.setMat4("viewMatrix", view);
            prog.setMat4("projectionMatrix", projection);
            prog.setVec3("lightPosition", lightPos);
            prog.setVec3("lightColor", lightColor);
            prog.setVec3("viewPosition", cameraPos);
            prog.setFloat("shiness", 64);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 36, 36 * 9 + 3);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}