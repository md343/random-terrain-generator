#version 430 compatibility
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
out vec3 Pos;
out vec3 Norm;

uniform mat4 model;
uniform mat4 camMat;

void main()
{
	gl_Position = camMat * model * vec4(pos, 1.0);
	Pos = pos;
	Norm = norm;
}