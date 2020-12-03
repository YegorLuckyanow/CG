#include "figures.h"

void getRectangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color, float * rectVertices)
{
    rectVertices[0] = point1.x;
    rectVertices[1] = point1.y;
    rectVertices[2] = point1.z;
    rectVertices[9] = point2.x;
    rectVertices[10] = point2.y;
    rectVertices[11] = point2.z;
    rectVertices[18] = point3.x;
    rectVertices[19] = point3.y;
    rectVertices[20] = point3.z;
    rectVertices[45] = point1.x;
    rectVertices[46] = point1.y;
    rectVertices[47] = point1.z;
    rectVertices[27] = point3.x;
    rectVertices[28] = point3.y;
    rectVertices[29] = point3.z;
    glm::vec3 tmp = point3 + point1 - point2;
    rectVertices[36] = tmp.x;
    rectVertices[37] = tmp.y;
    rectVertices[38] = tmp.z;
    glm::vec3 norm = glm::normalize(glm::cross(point1 - point2, point3 - point2));
    for (int i = 0; i < 6 * 9; i += 9)
    {
        rectVertices[i + 3] = norm.x;
        rectVertices[i + 4] = norm.y;
        rectVertices[i + 5] = norm.z;
        rectVertices[i + 6] = color.r;
        rectVertices[i + 7] = color.g;
        rectVertices[i + 8] = color.b;
    }
}

void getCube(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, glm::vec3 color, float * cubeVertices)
{
    getRectangle(point1, point2, point4, color, cubeVertices);
    getRectangle(point4, point2, point3, color, cubeVertices + 6 * 9);
    getRectangle(point3, point2, point1, color, cubeVertices + 2 * 6 * 9);
    getRectangle(point3 + point1 - point2, point1, point4 + point1 - point2, color, cubeVertices + 3 * 6 * 9);
    getRectangle(point4 + point3 - point2, point3, point1 + point3 - point2, color, cubeVertices + 4 * 6 * 9);
    getRectangle(point1 + point4 - point2, point4, point3 + point4 - point2, color, cubeVertices + 5 * 6 * 9);
}

void getTriangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color, float * trVertices)
{
    glm::vec3 norm = glm::normalize(glm::cross(point1 - point2, point3 - point2));
    float tmp[] = {
        point1.x, point1.y, point1.z, norm.x, norm.y, norm.z, color.r, color.g, color.b,
        point2.x, point2.y, point2.z, norm.x, norm.y, norm.z, color.r, color.g, color.b,
        point3.x, point3.y, point3.z, norm.x, norm.y, norm.z, color.r, color.g, color.b
    };
    for (int i = 0; i < 27; ++i)
    {
        trVertices[i] = tmp[i];
    }
}
