#version 430 core

in vec2 texcoord;

out vec4 fcolor;

uniform sampler2D diffuseMap;

void main()
{
	fcolor = texture(diffuseMap, texcoord);
}
