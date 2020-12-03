#pragma once

#include<glm/glm.hpp>
void getRectangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color, float *rectVertices);
void getCube(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4, glm::vec3 color, float *cubeVertices);
void getTriangle(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color, float *trVertices);