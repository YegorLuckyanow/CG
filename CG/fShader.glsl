#version 330 core
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;
uniform float shiness;
uniform sampler2D depthMap;

float calcShad(vec4 fPosLight, vec3 normal, vec3 lightDir)
{
    vec3 projCoords = fPosLight.xyz / fPosLight.w;
	if (projCoords.z > 1.0)
	{
		return 0.0;
	}
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(depthMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    return shadow;
}  

in vec3 fPosition;
in vec3 vNormal;
in vec3 vColor;
in vec4 fPosLight;

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
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0), shiness);
	vec3 specular = specularStrength * spec * lightColor;  

	float shad = 1.0 - calcShad(fPosLight, norm, lightDir);
	//shad = 1.0;

	FragColor = vec4((shad * (ambient + diffuse + specular)) * vColor, 1.0);
}