#version 430 core
 
#define POINT	    0 
#define DIRECTIONAL 1 
#define SPOTLIGHT   2 
#define MAX_LIGHTS  5

in vec3 position;
in vec3 normal;
in vec2 texcoord;
 
out vec4 fcolor; // pixel to draw

uniform struct Light
 {
	int type;
	vec3 ambient;
	vec3 color;
	vec4 position;
	vec3 direction; 
	float cutoff; 
	float exponent; 
 } lights[MAX_LIGHTS];

 uniform struct Material
 {
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
} material;
 
 uniform int light_count;
 uniform vec3 ambient_color;

layout (binding = 0) uniform sampler2D diffuseMap;
 
 void phong(Light light, vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular)
 {
	// direction vector to light 
	// calculate light direction (unit vector)
	vec3 light_dir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(vec3(light.position) - position); 

	// if spotlight, compute intensity based on angle to cutoff 
	float spot_intensity = 1; 
	if (light.type == SPOTLIGHT) 
	{ 
		// get cosine of light direction and direction vector from light 
		float cosine = dot(light.direction, -light_dir); 
		// get angle
		float angle = acos(cosine); 

		// if inside of cutoff, set spot intensity
		spot_intensity = (angle < light.cutoff) ? pow(cosine, light.exponent) : 0; 
	} 

	// DIFFUSE
	// calculate light intensity with dot product (normal * light direction)
	float intensity = max(dot(light_dir, normal), 0) * spot_intensity; 
	// calculate diffuse color
	diffuse = light.color * material.color * intensity;

	// SPECULAR
	specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_dir, normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0);
		intensity = pow(intensity, material.shininess);
		specular = light.color * material.color * intensity;
	}
 }

void main()
{
	fcolor = vec4(ambient_color, 1) * texture(diffuseMap, texcoord);

	for (int i = 0; i < light_count; i++) 
	{ 
		vec3 diffuse; 
		vec3 specular; 
  
		phong(lights[i], position, normal, diffuse, specular); 
		fcolor += (vec4(diffuse, 1) * texture(diffuseMap, texcoord)) + vec4(specular, 1);
	}
}