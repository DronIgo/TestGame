#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec3 Normal;
out vec2 Tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() 
{
	gl_Position = proj * view * model * vec4(aPos, 1.0);//vec4(aTex.xy, 0.0, 1.0);//
	Normal = aNormal;
	Tex = aTex;
};