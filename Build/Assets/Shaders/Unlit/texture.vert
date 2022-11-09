#version 430 core 

in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;

out vec2 texcoord;

uniform struct Material
{
	vec2 uv_tiling;
	vec2 uv_offset;
} material;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	texcoord = (vtexcoord * material.uv_tiling) + material.uv_offset;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}
