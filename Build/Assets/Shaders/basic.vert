#version 430 core 
in layout(location = 0) vec3 vposition; // 0
in layout(location = 1) vec3 vcolor; // 1
in layout(location = 2) vec2 vtexcoord; // 2

out vec3 color;
out vec2 texcoord;

uniform float scale;
uniform mat4 mvp;

void main()
{
	color = vcolor;
	texcoord = vtexcoord;

	vec4 tposition = mvp * vec4(vposition * scale, 1.0);
	gl_Position = tposition;
}