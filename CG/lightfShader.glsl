#version 330 core

in vec3 fPosition;
in vec3 vNormal;
in vec3 vColor;
in vec3 TBN;
in vec3 plane;

out vec4 FragColor;

void main()
{
	FragColor = vec4(vColor, 1.0);
}