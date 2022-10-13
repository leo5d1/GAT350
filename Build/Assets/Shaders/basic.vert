#version 430 core 

in layout(location = 0) vec3 vposition; // 0
in layout(location = 1) vec3 vcolor; // 1

out vec3 color;

uniform float scale;
uniform mat4 transform;

void main()
{
	color = vcolor;
	vec4 tposition = vec4(vposition, 1) * transform;
	gl_Position = tposition;
}
