#version 330 core
//uniform mat4 modelMatrix;
//uniform mat4 projectionMatrix;
//uniform mat4 viewMatrix;

uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;
uniform float shiness;
uniform sampler2D textureIm;
uniform sampler2D depthMap;
uniform sampler2D normalMap;
uniform sampler2D parallaxMap;
uniform vec3 color;
uniform float heightScale = 0.1;
uniform vec3 smokeColor;
uniform float smokeInt;

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
	float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.01);
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    return shadow;
}  

in mat3 TBN;

vec2 parallaxMapping(vec2 texCoords, vec3 viewDirInp)
{ 
	vec3 viewDir = transpose(TBN) * viewDirInp;
    float height =  texture(parallaxMap, texCoords).r;    
    vec2 p = viewDir.xy / viewDir.z * (height * heightScale);
    return texCoords - p;    
} 

in vec3 fPosition;
in vec3 vNormal;
in vec3 vColor;
in vec4 fPosLight;
in VS_OUT {
	flat int plane;
} fs_in;
in vec2 texCoordsIn;

out vec4 FragColor;

void main()
{
	int plane = fs_in.plane;
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
	vec3 viewDir = normalize(viewPosition - fPosition);

	vec2 texCoords = texCoordsIn;
	texCoords = parallaxMapping(texCoordsIn, viewDir);
	if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
		discard;
	//texCoords = texCoordsIn;
	vec3 norm = normalize(vNormal);
	if (plane == 0)
	{
		norm = texture(normalMap, texCoords).rgb;
		norm = norm * 2.0 - 1.0;
		norm = normalize(TBN * norm);
	}
	vec3 lightDir = normalize(lightPosition - fPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;
	vec3 halfwayDir = normalize(lightDir + viewDir);
	//vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, halfwayDir), 0.0), shiness);
	vec3 specular = specularStrength * spec * lightColor;  

	float shad = 1.0 - calcShad(fPosLight, norm, lightDir);
	//shad = 1.0;

	float smoke = abs(atan(length(fPosition - viewPosition) / smokeInt)) * 2 / 3.141;

	vec3 resColor;
	if (plane == 0)
	{
		//resColor = texture(textureIm, texCoords).rgb;
		resColor = color;
	}
	else
	{
		resColor = vColor;
	}
	//smoke = 0;
	FragColor = vec4(smoke * smokeColor + (1.0 - smoke) * (shad * (ambient + diffuse + specular)) * resColor, 1.0);
}