#version 430 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

void main()
{
	UV = (vertexPosition_modelspace.xy+vec2(1,1))/2.0;
	gl_Position =  vec4(vertexPosition_modelspace,1);
}

