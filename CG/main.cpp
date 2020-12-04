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
    Shader shProg("shadowvshader.glsl", "shadowfshader.glsl");
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
        glm::vec3 ang = glm::vec3(-1.0f) + 0.3f * i * glm::vec3(i % 3 == 1 ? -1.0f : 1.0f, i % 2 == 0 ? -1.0f : 1.0f, i % 3 == 2 ? -1.0f : 1.0f);
        getCube(glm::vec3(i * mult, 0.0f, 0.0f) + ang, glm::vec3(0.0f, -0.0f, -0.0f) + ang, glm::vec3(-0.0f, i * mult, -0.0f) + ang, glm::vec3(0.0f, 0.0f, i * mult) + ang, glm::vec3(0.0, 1.0, 1.0), vertices + i * 36 * 9);
    }
    getTriangle(glm::vec3(-1000.0, -5.0, -1000.0), glm::vec3(-1000.0, -5.0, 1000.0), glm::vec3(1000.0, -5.0, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), vertices + 36 * 9 * 10);

    unsigned int depthFBO;
    glGenFramebuffers(1, &depthFBO);
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
        SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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
    float near_plane = 1.0f, far_plane = 7.5f;
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        hndKbInput(window, cameraUp);
        if (scene == 0)
        {
            cameraPos = glm::vec3(sin(glfwGetTime()) * 20.0f, 0.0f, cos(glfwGetTime()) * 20.0f);
            projection = glm::perspective(glm::radians(45.0f), wWidth / wHeight, 0.1f, 100.0f);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            glm::vec3 lightPos = glm::vec3(5.0f, 0.0f, -1.0f);
            glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            getCube(glm::vec3(0.1f, 0.0f, 0.0f) + lightPos, lightPos, glm::vec3(-0.0f, 0.1f, -0.0f) + lightPos, glm::vec3(0.0f, 0.0f, 0.1f) + lightPos, lightColor, vertices);
            glBufferData(GL_ARRAY_BUFFER, (10 * 36 * 9 + 3 * 9) * sizeof(float), vertices, GL_STATIC_DRAW);
            view = glm::lookAt(cameraPos, cameraTarg, cameraUp);
            glm::mat4 lightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

            shProg.use();
            shProg.setMat4("lightProj", lightProj);
            shProg.setMat4("lightView", lightView);
            shProg.setMat4("model", model);
            glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
            glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
            glClear(GL_DEPTH_BUFFER_BIT);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 36, 36 * 9);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

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
            glm::mat4 lightMatrix = lightProj * lightView;
            prog.setMat4("lightMatrix", lightMatrix);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 36, 36 * 9 + 3);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}