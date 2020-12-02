#version 330 core
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 fPosition;
out vec3 vNormal;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

void main() 
{
    vNormal = normal;
    fPosition = vec3(modelMatrix * vec4(position, 1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4( position, 1.0 );
}