#version 430 core

in vec3 reflect_dir;

out vec4 fcolor;

uniform samplerCube Cubemap;

void main()
{
	fcolor = texture(Cubemap, reflect_dir);
}
