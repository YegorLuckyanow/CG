#version 330 core

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
 
out VS_OUT {
    vec3 color;
	vec3 normal;
} vs_out;
 
void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0); 
    vs_out.color = aColor;
	vs_out.normal = aNormal;
}  