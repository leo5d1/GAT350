#version 430 core

in vec3 color;

out vec4 fcolor;

uniform vec3 tint;

void main()
{
	fcolor = vec4(color * tint, 1.0);
}
