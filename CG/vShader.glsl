#version 330 core
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 lightMatrix;

out vec3 fPosition;
out vec3 vNormal;
out vec3 vColor;
out vec4 fPosLight;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

void main() 
{
    vNormal = transpose(inverse(mat3(modelMatrix))) * normal;
	vColor = color;
    fPosition = vec3(modelMatrix * vec4(position, 1.0));
	fPosLight = lightMatrix * vec4(fPosition, 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4( position, 1.0 );
}