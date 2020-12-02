#version 330 core
layout (location = 0) in vec3 aPos;
 
uniform mat4 lightProj;
uniform mat4 lightView;
uniform mat4 model;
 
void main()
{
    gl_Position = lightProj * lightView * model * vec4(aPos, 1.0);
}  