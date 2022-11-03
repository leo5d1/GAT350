#version 430 core 
 
in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;
 
out vec3 position;
out vec3 normal;
out vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
 
void main()
{
	// create model view mattrix
	mat4 model_view = view * model;
	// transfom normals to view space
	normal = mat3(model_view) * vnormal;
	// transform position to view space
	position = vec3(model_view * vec4(vposition, 1));
	// pass-through texcoord
	texcoord = vtexcoord;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}