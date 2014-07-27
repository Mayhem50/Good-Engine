#version 430 core

layout (location = 0) in vec3 uvw;

out vec4 color;

uniform samplerCube environementCubeMap;
void main ()
{
	color = texture(environementCubeMap, uvw.stp);	
}