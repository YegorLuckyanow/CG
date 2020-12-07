#version 330 core
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 lightMatrix;

out vec3 fPosition;
out vec3 vNormal;
out vec3 vColor;
out vec4 fPosLight;
out mat3 TBN;
out VS_OUT {
	flat int plane;
} vs_out;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

void main() 
{
	int plane;
    vNormal = transpose(inverse(mat3(modelMatrix))) * normal;
	vColor = color;
    fPosition = vec3(modelMatrix * vec4(position, 1.0));
	fPosLight = lightMatrix * vec4(fPosition, 1.0);
	vec3 T = normalize(vec3(modelMatrix * vec4(tangent, 0.0)));
    vec3 B = normalize(vec3(modelMatrix * vec4(bitangent, 0.0)));
    vec3 N = normalize(vec3(modelMatrix * vec4(normal, 0.0)));
	TBN = mat3(T, B, N);
	if (tangent == 0)
	{
		plane = 1;
	}
	else
	{
		plane = 0;
	}
	vs_out.plane = plane;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4( position, 1.0 );
}