#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;
 
uniform sampler2D screenTexture;
uniform vec3 color;
uniform int neg;
 
void main()
{ 
	if (neg == 1)
	{
		FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);
	}
	else
	{
		FragColor = texture(screenTexture, TexCoords);
	}
	//FragColor = vec4(color, 1.0);
}