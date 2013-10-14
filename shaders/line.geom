#version 150

layout (points) in;
layout (triangle_strip, max_vertices = 9) out;

uniform mat4 PMatrix;
uniform vec3 eyePos;

in vec3 v[1];
in vec4 vertexColour[1];

out vec4 colour;

void main()
{
    vec3 p = gl_in[0].gl_Position.xyz;
    vec3 E = normalize(eyePos - p);
    vec3 V = normalize(v[0]);
    vec3 T = normalize(cross(E, V));
    
    float w = 0.1;
    
    gl_Position = PMatrix * vec4(p + w * T, 1.);
    colour = vertexColour[0];
    EmitVertex();
    
    gl_Position = PMatrix * vec4(p - w * T, 1.);
    colour = vertexColour[0];
    EmitVertex();
    
    gl_Position = PMatrix * vec4(p - w * T + v[0], 1.);
    colour = vertexColour[0];
    EmitVertex();
    
    EndPrimitive();
    
    gl_Position = PMatrix * vec4(p - w * T + v[0], 1.);
    colour = vertexColour[0];
    EmitVertex();
    
    gl_Position = PMatrix * vec4(p + w * T + v[0], 1.);
    colour = vertexColour[0];
    EmitVertex();
    
    gl_Position = PMatrix * vec4(p + w * T, 1.);
    colour = vertexColour[0];
    EmitVertex();
    
    EndPrimitive();
}