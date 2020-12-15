#version 330 core

uniform float time;
uniform float time0;

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 fColor;
out vec3 vNormal;

in VS_OUT {
    vec3 color;
	vec3 normal;
} gs_in[]; 

vec3 getNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}  

vec4 explode(vec4 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((time - time0) / 2.0) * magnitude; 
    return position + vec4(direction, 0.0);
}

/*vec4 explode(vec4 position, vec3 normal)
{
	return position;
}*/
 
void main() {    
	vec3 normal = getNormal();
    gl_Position = explode(gl_in[0].gl_Position, vec3(normal.x * (1 + time - time0), normal.yz));
    fColor = gs_in[0].color;
	vNormal = gs_in[0].normal;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, normal);
    fColor = gs_in[1].color;
	vNormal = gs_in[1].normal;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, normal);
    fColor = gs_in[2].color;
	vNormal = gs_in[2].normal;
    EmitVertex();
    EndPrimitive();
}