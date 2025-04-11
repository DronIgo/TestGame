#version 450 core

out gl_PerVertex { vec4 gl_Position; };

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 aColor;

layout (location = 0) out v_output
{
    vec3 color;
} v_out;

void main() 
{
	gl_Position = aPos;
	v_out.color = aColor;
}