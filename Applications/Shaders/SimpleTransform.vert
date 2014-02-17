#version 430 core

// Input vertex data, different for all executions of this shader.

//layout(location = 0) in vec3 vertexPosition;
//layout(location = 1) in vec3 vertexColor;
//layout(location = 2) in vec3 vertexNormal;

struct VertexData
{
	vec3 position;
	vec3 color;
	vec3 normal;
	vec2 uv;
};

in VertexData data;

layout (std140, binding = 0) uniform WorldDataBlock
{
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
}WorldData;

// Output data ; will be interpolated for each fragment.
out VertexData outData;

// Values that stay constant for the whole mesh.
layout(location = 12) uniform mat4 MVP;

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

void main()
{	
	mat4 MVP = WorldData.projectionMatrix * WorldData.viewMatrix * WorldData.modelMatrix;
	//mat4 matrix = MVP;	
	gl_Position =  MVP * vec4(data.position, 1);
	outData = data;
}

