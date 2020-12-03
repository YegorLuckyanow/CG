#version 330 core
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;

in vec3 fPosition;
in vec3 vNormal;
in vec3 vColor;

out vec4 FragColor;

void main()
{
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	vec3 norm = normalize(vNormal);
	vec3 lightDir = normalize(lightPosition - fPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPosition - fPosition);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	//vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;  
	FragColor = vec4((ambient + diffuse + specular) * vColor, 1.0);
}