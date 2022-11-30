#version 430 core  
  
in layout(location = 0) vec3 vposition; 
in layout(location = 1) vec2 vtexcoord; 
  
out vec2 texcoord; 
  
void main() 
{ 
	texcoord = vtexcoord; 
	gl_Position = vec4(vposition.x, vposition.y, 0.0, 1.0); 
} 