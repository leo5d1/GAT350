#version 430 core
 
#define POINT  0 
#define DIRECTIONAL 1 
#define SPOTLIGHT 2 

in vec3 position;
in vec3 normal;
in vec2 texcoord;
 
out vec4 fcolor; // pixel to draw

struct Light
 {
	int type;
	vec3 ambient;
	vec3 color;
	vec4 position;
	vec3 direction; 
	float cutoff; 
	float exponent; 
 };

 struct Material
 {
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
};

uniform Light light;
uniform Material material;
 
layout (binding = 0) uniform sampler2D diffuseMap;
layout (binding = 1) uniform sampler2D specularMap;
 
 void phong(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
 {
	// AMBIENT
	ambient = light.ambient * material.color;

	// DIFFUSE
	// direction vector to light 
	vec3 light_dir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(vec3(light.position) - position); 

	// if spotlight, compute intensity based on angle to cutoff 
	float spot_intensity = 1; 
	if (light.type == SPOTLIGHT) 
	{ 
		// get cosine of light direction and direction vector from light 
		float cosine = dot(light.direction, -light_dir); 
		// get angle using acos() of the cosine (returns the angle) 
		float angle = acos(cosine); 
		spot_intensity = (angle < light.cutoff) ? pow(cosine, light.exponent) : 0; 
	} 

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
	

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	phong(position, normal, ambient, diffuse, specular);

	vec2 ttexcoord = (texcoord * material.uv_tiling) + material.uv_offset;

	//vec4 texture_color = mix(texture(texture1, ttexcoord), texture(texture2, ttexcoord), 0.5);
	vec4 texture_color = texture(diffuseMap, ttexcoord);

	fcolor = vec4(ambient + diffuse, 1) * texture_color + (vec4(specular, 1) * texture(specularMap, ttexcoord));
}