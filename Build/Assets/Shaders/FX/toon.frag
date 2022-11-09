#version 430 core
 
#define POINT	    0 
#define DIRECTIONAL 1 
#define SPOTLIGHT   2 

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
 } light;

 uniform struct Material
 {
	vec3 color;
	float shininess;
	vec2 uv_tiling;
	vec2 uv_offset;
} material;
 
 int levels = 5;
 const float scale_factor = 1.0 / levels;

 void toon(vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
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

	// AMBIENT
	ambient = light.ambient * material.color;

	// DIFFUSE
	// calculate light intensity with dot product (normal * light direction)
	float intensity = max(dot(light_dir, normal), 0) * spot_intensity; 

	intensity = floor(intensity * levels) * scale_factor;

	// calculate diffuse color
	diffuse = light.color * material.color * intensity;

	// SPECULAR
	specular = vec3(0);
//	if (intensity > 0)
//	{
//		vec3 reflection = reflect(-light_dir, normal);
//		vec3 view_dir = normalize(-vec3(position));
//		intensity = max(dot(reflection, view_dir), 0);
//		intensity = pow(intensity, material.shininess);
//		specular = light.color * material.color * intensity;
//	}
 }

void main()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	toon(position, normal, ambient, diffuse, specular);

	fcolor = vec4(ambient + diffuse, 1) + vec4(specular, 1);
}