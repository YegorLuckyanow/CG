#include "figures.h"

int args_nmb = 15;

void getRectangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color, float * rectVertices)
{
    rectVertices[0] = point1.x;
    rectVertices[1] = point1.y;
    rectVertices[2] = point1.z;
    rectVertices[15] = point2.x;
    rectVertices[16] = point2.y;
    rectVertices[17] = point2.z;
    rectVertices[30] = point3.x;
    rectVertices[31] = point3.y;
    rectVertices[32] = point3.z;
    rectVertices[75] = point1.x;
    rectVertices[76] = point1.y;
    rectVertices[77] = point1.z;
    rectVertices[45] = point3.x;
    rectVertices[46] = point3.y;
    rectVertices[47] = point3.z;
    glm::vec3 tmp = point3 + point1 - point2;
    rectVertices[60] = tmp.x;
    rectVertices[61] = tmp.y;
    rectVertices[62] = tmp.z;
    rectVertices[6] = 1.0f;
    rectVertices[7] = 0.0f;
    rectVertices[args_nmb + 6] = 0.0f;
    rectVertices[args_nmb + 7] = 0;
    rectVertices[2 * args_nmb + 6] = 1.0f;
    rectVertices[2 * args_nmb + 7] = 1.0f;
    rectVertices[3 * args_nmb + 6] = 0.0f;
    rectVertices[3 * args_nmb + 7] = 1.0f;
    rectVertices[4 * args_nmb + 6] = 1.0f;
    rectVertices[4 * args_nmb + 7] = 1.0f;
    rectVertices[5 * args_nmb + 6] = 1.0f;
    rectVertices[5 * args_nmb + 7] = 0.0f;
    rectVertices[0 * args_nmb + 8] = rectVertices[1 * args_nmb + 8] = rectVertices[2 * args_nmb + 8] = rectVertices[3 * args_nmb + 8] = rectVertices[4 * args_nmb + 8] = rectVertices[5 * args_nmb + 8] = 0.0f;
    glm::vec3 norm = glm::normalize(glm::cross(point1 - point2, point3 - point2));
    glm::vec3 tan = glm::normalize(point1 - point2);
    glm::vec3 bit = glm::normalize(point3 - point2);
    for (int i = 0; i < 6 * args_nmb; i += args_nmb)
    {
        rectVertices[i + 3] = norm.x;
        rectVertices[i + 4] = norm.y;
        rectVertices[i + 5] = norm.z;
        /*rectVertices[i + 6] = color.r;
        rectVertices[i + 7] = color.g;
        rectVertices[i + 8] = color.b;*/
        rectVertices[i + 9] = tan.x;
        rectVertices[i + 10] = tan.y;
        rectVertices[i + 11] = tan.z;
        rectVertices[i + 12] = bit.x;
        rectVertices[i + 13] = bit.y;
        rectVertices[i + 14] = bit.z;
    }
}

void getCRectangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color, float * rectVertices)
{
    rectVertices[0] = point1.x;
    rectVertices[1] = point1.y;
    rectVertices[2] = point1.z;
    rectVertices[15] = point2.x;
    rectVertices[16] = point2.y;
    rectVertices[17] = point2.z;
    rectVertices[30] = point3.x;
    rectVertices[31] = point3.y;
    rectVertices[32] = point3.z;
    rectVertices[75] = point1.x;
    rectVertices[76] = point1.y;
    rectVertices[77] = point1.z;
    rectVertices[45] = point3.x;
    rectVertices[46] = point3.y;
    rectVertices[47] = point3.z;
    glm::vec3 tmp = point3 + point1 - point2;
    rectVertices[60] = tmp.x;
    rectVertices[61] = tmp.y;
    rectVertices[62] = tmp.z;
    glm::vec3 norm = glm::normalize(glm::cross(point1 - point2, point3 - point2));
    glm::vec3 tan = glm::normalize(point1 - point2);
    glm::vec3 bit = glm::normalize(point3 - point2);
    for (int i = 0; i < 6 * args_nmb; i += args_nmb)
    {
        rectVertices[i + 3] = norm.x;
        rectVertices[i + 4] = norm.y;
        rectVertices[i + 5] = norm.z;
        rectVertices[i + 6] = color.r;
        rectVertices[i + 7] = color.g;
        rectVertices[i + 8] = color.b;
        rectVertices[i + 9] = tan.x;
        rectVertices[i + 10] = tan.y;
        rectVertices[i + 11] = tan.z;
        rectVertices[i + 12] = bit.x;
        rectVertices[i + 13] = bit.y;
        rectVertices[i + 14] = bit.z;
    }
}

void getCube(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, glm::vec3 color, float * cubeVertices)
{
    getRectangle(point1, point2, point4, color, cubeVertices);
    getRectangle(point4, point2, point3, color, cubeVertices + 6 * args_nmb);
    getRectangle(point3, point2, point1, color, cubeVertices + 2 * 6 * args_nmb);
    getRectangle(point3 + point1 - point2, point1, point4 + point1 - point2, color, cubeVertices + 3 * 6 * args_nmb);
    getRectangle(point4 + point3 - point2, point3, point1 + point3 - point2, color, cubeVertices + 4 * 6 * args_nmb);
    getRectangle(point1 + point4 - point2, point4, point3 + point4 - point2, color, cubeVertices + 5 * 6 * args_nmb);
}

void getCCube(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, glm::vec3 color, float * cubeVertices)
{
    getCRectangle(point1, point2, point4, color, cubeVertices);
    getCRectangle(point4, point2, point3, color, cubeVertices + 6 * args_nmb);
    getCRectangle(point3, point2, point1, color, cubeVertices + 2 * 6 * args_nmb);
    getCRectangle(point3 + point1 - point2, point1, point4 + point1 - point2, color, cubeVertices + 3 * 6 * args_nmb);
    getCRectangle(point4 + point3 - point2, point3, point1 + point3 - point2, color, cubeVertices + 4 * 6 * args_nmb);
    getCRectangle(point1 + point4 - point2, point4, point3 + point4 - point2, color, cubeVertices + 5 * 6 * args_nmb);
}

void getTriangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color, float * trVertices)
{
    glm::vec3 norm = glm::normalize(glm::cross(point1 - point2, point3 - point2));
    float tmp[] = {
        point1.x, point1.y, point1.z, norm.x, norm.y, norm.z, color.r, color.g, color.b, 0, 0, 0, 0, 0, 0,
        point2.x, point2.y, point2.z, norm.x, norm.y, norm.z, color.r, color.g, color.b, 0, 0, 0, 0, 0, 0,
        point3.x, point3.y, point3.z, norm.x, norm.y, norm.z, color.r, color.g, color.b, 0, 0, 0, 0, 0, 0
    };
    for (int i = 0; i < args_nmb * 3; ++i)
    {
        trVertices[i] = tmp[i];
    }
}
