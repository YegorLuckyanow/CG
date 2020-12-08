#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 5) out;
 
void build_house(vec4 position)
{    
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);    // 1:нижн€€-лева€
    EmitVertex();   
    gl_Position = position + vec4( 0.2, -0.2, 0.0, 0.0);    // 2:нижн€€-права€
    EmitVertex();
    gl_Position = position + vec4(-0.2,  0.2, 0.0, 0.0);    // 3:верхн€€-лева€
    EmitVertex();
    gl_Position = position + vec4( 0.2,  0.2, 0.0, 0.0);    // 4:верхн€€-права€
    EmitVertex();
    gl_Position = position + vec4( 0.0,  0.4, 0.0, 0.0);    // 5:верхн€€
    EmitVertex();
    EndPrimitive();
}
 
void main() {    
    build_house(gl_in[0].gl_Position);
}