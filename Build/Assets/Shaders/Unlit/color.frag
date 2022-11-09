#version 430 core

in vec3 color;

out vec4 fcolor;

void main()
{
	fcolor = vec4(color, 1);
}
