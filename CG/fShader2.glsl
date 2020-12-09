#version 330 core
out vec4 FragColor;
in vec3 fColor;
in vec3 vNormal;
 
void main()
{
	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(vNormal);
	vec3 lightDir = vec3(1.0f, 1.0f, 1.0f);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

    FragColor = vec4(fColor, 1.0);   
}  