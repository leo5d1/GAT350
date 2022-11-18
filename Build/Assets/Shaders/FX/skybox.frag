#version 430 core

in vec3 texcoord;

out vec4 fcolor;

uniform samplerCube Cubemap;

void main()
{
	fcolor = texture(Cubemap, texcoord);
}
