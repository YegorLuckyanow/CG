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
    int args_nmb = 15;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "Hello, OpenGL", NULL, NULL);
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
    Shader prog2("vShader2.glsl", "gShader.glsl", "fShader2.glsl");
    Shader postProg("postvShader.glsl", "postfShader.glsl");
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
    float *vertices = new float[36 * args_nmb * 10 + 3 * args_nmb];
    for (int i = 1; i < 10; ++i)
    {
        float mult = 0.25f;
        glm::vec3 ang = glm::vec3(-1.0f) + 0.3f * i * glm::vec3(i % 3 == 1 ? -1.0f : 1.0f, i % 2 == 0 ? -1.0f : 1.0f, i % 3 == 2 ? -1.0f : 1.0f);
        getCube(glm::vec3(i * mult, 0.0f, 0.0f) + ang, glm::vec3(0.0f, -0.0f, -0.0f) + ang, glm::vec3(-0.0f, i * mult, -0.0f) + ang, glm::vec3(0.0f, 0.0f, i * mult) + ang, glm::vec3(0.0, 1.0, 1.0), vertices + i * 36 * args_nmb);
    }
    getTriangle(glm::vec3(-1000.0, -5.0, -1000.0), glm::vec3(-1000.0, -5.0, 1000.0), glm::vec3(1000.0, -5.0, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), vertices + 36 * args_nmb * 10);
    float *vertices2 = new float[36 * args_nmb * 10 + 3 * args_nmb];
    for (int i = 1; i < 10; ++i)
    {
        float mult = 0.25f;
        glm::vec3 ang = glm::vec3(-1.0f) + 0.3f * i * glm::vec3(i % 3 == 1 ? -1.0f : 1.0f, i % 2 == 0 ? -1.0f : 1.0f, i % 3 == 2 ? -1.0f : 1.0f);
        getCCube(glm::vec3(i * mult, 0.0f, 0.0f) + ang, glm::vec3(0.0f, -0.0f, -0.0f) + ang, glm::vec3(-0.0f, i * mult, -0.0f) + ang, glm::vec3(0.0f, 0.0f, i * mult) + ang, glm::vec3(0.0, 1.0, 1.0), vertices2 + i * 36 * args_nmb);
    }
    unsigned int depthFBO;
    glGenFramebuffers(1, &depthFBO);
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    unsigned int depthMap;
    glActiveTexture(GL_TEXTURE0);
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

    unsigned int postFBO;
    glGenFramebuffers(1, &postFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, postFBO);
    unsigned int postText;
    glGenTextures(1, &postText);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, postText);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wWidth, wHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, postText, 0); 
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, wWidth, wHeight);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    //glDrawBuffer(GL_NONE);
    //glReadBuffer(GL_NONE);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    float *postRect = new float[args_nmb * 6];
    getRectangle(glm::vec3(1.0, -1.0, 0.0), glm::vec3(-1.0, -1.0, 0.0), glm::vec3(-1.0, 1.0, 0.0), glm::vec3(1.0f, 1.0f, 1.0f), postRect);
    unsigned int postVAO;
    glGenVertexArrays(1, &postVAO);
    glBindVertexArray(postVAO);
    unsigned int postVBO;
    glGenBuffers(1, &postVBO);
    glBindBuffer(GL_ARRAY_BUFFER, postVBO);
    glBufferData(GL_ARRAY_BUFFER, (6 * args_nmb) * sizeof(float), postRect, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, args_nmb * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, args_nmb * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("normalMap.png", &width, &height, &nrChannels, 0);
    glActiveTexture(GL_TEXTURE1);
    unsigned int normMap;
    glGenTextures(1, &normMap);
    glBindTexture(GL_TEXTURE_2D, normMap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    data = stbi_load("parallaxMap.png", &width, &height, &nrChannels, 0);
    glActiveTexture(GL_TEXTURE2);
    unsigned int parMap;
    glGenTextures(1, &parMap);
    glBindTexture(GL_TEXTURE_2D, parMap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    data = stbi_load("imText.png", &width, &height, &nrChannels, 0);
    glActiveTexture(GL_TEXTURE3);
    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (10 * 36 * args_nmb + 3 * args_nmb) * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, args_nmb * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, args_nmb * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, args_nmb * sizeof(float), (void*)(6 * sizeof(float)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, args_nmb * sizeof(float), (void*)(9 * sizeof(float)));
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, args_nmb * sizeof(float), (void*)(12 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);

    unsigned int VAO2;
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);
    unsigned int VBO2;
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, (10 * 36 * args_nmb + 3 * args_nmb) * sizeof(float), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, args_nmb * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, args_nmb * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, args_nmb * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarg = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 smokeColor = glm::vec3(1.0f, 0.5f, 0.5f);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), wWidth / wHeight, 0.1f, 100.0f);
    float near_plane = 1.0f, far_plane = 7.5f;
    float time, time0;
    int neg = 0;
    time0 = glfwGetTime();
    float smokeInt = 10.0f;
    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_DEPTH_TEST);
        hndKbInput(window, scene, time0, neg, smokeInt);
        cameraPos = glm::vec3(sin(glfwGetTime()) * 20.0f, 0.0f, cos(glfwGetTime()) * 20.0f);
        projection = glm::perspective(glm::radians(45.0f), wWidth / wHeight, 0.1f, 100.0f);
        view = glm::lookAt(cameraPos, cameraTarg, cameraUp);
        fbSzCallback(window, wWidth, wHeight);
        if (scene == 0)
        {
            glEnable(GL_DEPTH_TEST);
            glActiveTexture(GL_TEXTURE0);
            glm::vec3 lightPos = glm::vec3(5.0f, 0.0f, -1.0f);
            glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            getCCube(glm::vec3(0.1f, 0.0f, 0.0f) + lightPos, lightPos, glm::vec3(-0.0f, 0.1f, -0.0f) + lightPos, glm::vec3(0.0f, 0.0f, 0.1f) + lightPos, lightColor, vertices);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, (10 * 36 * args_nmb + 3 * args_nmb) * sizeof(float), vertices, GL_STATIC_DRAW);
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

            glBindFramebuffer(GL_FRAMEBUFFER, postFBO);
            glClearColor(smokeColor.r, smokeColor.g, smokeColor.b, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

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
            prog.setVec3("color", glm::vec3(0.0f, 1.0f, 1.0f));
            glm::mat4 lightMatrix = lightProj * lightView;
            prog.setMat4("lightMatrix", lightMatrix);
            glBindVertexArray(VAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, depthMap);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, normMap);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, parMap);
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, tex);
            glUniform1i(glGetUniformLocation(prog.ID, "depthMap"), 0);
            glUniform1i(glGetUniformLocation(prog.ID, "normalMap"), 1);
            prog.setInt("parallaxMap", 2);
            prog.setInt("textureIm", 3);
            prog.setVec3("smokeColor", smokeColor);
            prog.setFloat("smokeInt", smokeInt);
            glDrawArrays(GL_TRIANGLES, 36, 36 * 9 + 3);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            fbSzCallback(window, wWidth, wHeight);
            postProg.use();
            //postProg.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
            glBindVertexArray(postVAO);
            glDisable(GL_DEPTH_TEST);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE5);
            glBindTexture(GL_TEXTURE_2D, postText);
            postProg.setInt("screenTexture", 5);
            postProg.setInt("neg", neg);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        else if (scene == 1)
        {
            cameraPos = glm::vec3(sin(glfwGetTime()) * 20.0f, 0.0f, cos(glfwGetTime()) * 20.0f);
            projection = glm::perspective(glm::radians(45.0f), wWidth / wHeight, 0.1f, 100.0f);
            view = glm::lookAt(cameraPos, cameraTarg, cameraUp);
            glBindFramebuffer(GL_FRAMEBUFFER, postFBO);
            glEnable(GL_DEPTH_TEST);
            time = glfwGetTime();
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
            prog2.use();
            prog2.setMat4("modelMatrix", model);
            prog2.setMat4("viewMatrix", view);
            prog2.setMat4("projectionMatrix", projection);
            prog2.setFloat("time", time);
            prog2.setFloat("time0", time0);
            glBindVertexArray(VAO2);
            glDrawArrays(GL_TRIANGLES, 36, 36 * 9);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            fbSzCallback(window, wWidth, wHeight);
            postProg.use();
            //postProg.setVec3("color", glm::vec3(1.0f, 1.0f, 1.0f));
            glBindVertexArray(postVAO);
            glDisable(GL_DEPTH_TEST);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glActiveTexture(GL_TEXTURE5);
            glBindTexture(GL_TEXTURE_2D, postText);
            postProg.setInt("screenTexture", 5);
            postProg.setInt("neg", neg);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}