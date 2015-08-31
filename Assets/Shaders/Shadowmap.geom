#version 430 core

layout(triangles) in;
layout (triangle_strip, max_vertices = 3) out;

layout (std140, binding = 0) uniform WorldDataBlock
{
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 normalMatrix;
}worldData;

layout (location = 0) in vec3 normal[];

in gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
}gl_in[];

out Data
{
	vec3 normal;
	vec3 eyePos;
	vec3 lightDir;
	float attenuation;
	vec3 color;
} outData;

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

void main()
{
	mat4 MV = worldData.viewMatrix * worldData.modelMatrix;
	mat4 MVP =  worldData.projectionMatrix * MV;

	for(int idx = 0; idx < gl_in.length(); ++idx)
	{
		gl_Position = MVP *  gl_in[idx].gl_Position;
		outData.normal = normal[idx];
		EmitVertex();
	}

	EndPrimitive();
}
