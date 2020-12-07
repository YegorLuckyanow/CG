#version 330 core
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;
uniform float shiness;
uniform sampler2D depthMap;
uniform sampler2D normalMap;
uniform vec3 color;

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
in mat3 TBN;
in VS_OUT {
	flat int plane;
} fs_in;

out vec4 FragColor;

void main()
{
	int plane = fs_in.plane;
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(vNormal);
	/*if (plane == 0)
	{
		norm = texture(normalMap, vec2(vColor.r, vColor.g)).rgb;
		norm = norm * 2.0 - 1.0;
		norm = normalize(TBN * norm);
	}*/
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

	vec3 resColor;
	if (plane == 0)
	{
		resColor = color;
	}
	else
	{
		resColor = vColor;
	}
	FragColor = vec4((shad * (ambient + diffuse + specular)) * resColor, 1.0);
	/*if (plane == 0)
	{
		FragColor = texture(normalMap, vColor.rg);
	}*/
}