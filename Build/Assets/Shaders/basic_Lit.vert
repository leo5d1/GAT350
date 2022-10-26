#version 430 core 
 
in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
 
out vec2 texcoord;
 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
 
void main()
{
	texcoord = vtexcoord;
 
	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}