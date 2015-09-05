#version 430 core

layout(triangles, invocations = 32) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 normal[];

out Data
{
	vec3 normal;
	vec3 eyePos;
	vec3 lightDir;
	float attenuation;
	vec3 color;
} outData;

layout (std140, binding = 0) uniform WorldDataBlock
{
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 normalMatrix;
}worldData;

layout (std140, binding = 1) uniform LightTransformBlock
{ 
	mat4 VPMatrix[32];
}lightTransformData;

in gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
}gl_in[];

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

void main()
{
	for(int idx = 0; idx < gl_in.length(); ++idx)
	{
		gl_Position = VPMatrix[gl_InvocationID] *  gl_in[idx].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}
