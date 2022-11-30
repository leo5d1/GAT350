#version 430 core
 
in vec2 texcoord;
 
out vec4 fcolor;
 
uniform sampler2D diffuseMap;
uniform float time;
 
void main()
{
	vec3 color = texture(diffuseMap, texcoord).rgb;
	float avg = (color.r + color.g + color.b) / 3.0;
	fcolor = vec4(vec3(0, avg, 0), 1);
 
	//fcolor = texture(diffuseMap, texcoord);
}