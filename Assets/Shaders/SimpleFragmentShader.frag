#version 430 core

in vec3 fragmentColor;
// Ouput dat
layout(location = 0) out vec3 color;

void main()
{
	// Output color = red 
	color = vec3(1, 0, 0);
}