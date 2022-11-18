#version 430 core

in vec3 refract_dir;

out vec4 fcolor;

uniform samplerCube Cubemap;

void main()
{
	fcolor = texture(Cubemap, refract_dir);
}
