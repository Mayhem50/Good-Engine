#version 430 core

layout(triangles, invocations = 1) in;
layout (triangle_strip, max_vertices = 3) out;

layout (std140, binding = 0) uniform WorldDataBlock
{
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 normalMatrix;
}worldData;

layout (location = 0) out vec3 uvw;

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

void main ()
{
	mat4 MV = worldData.viewMatrix * worldData.modelMatrix;
	mat4 invMV = inverse(MV);
	vec3 camPos = invMV[3].xyz;
	
	for(int idx = 0; idx < gl_in.length(); ++idx)
	{
		uvw = vec3(gl_in[idx].gl_Position.x, -gl_in[idx].gl_Position.yz);
		gl_Position = worldData.projectionMatrix * MV * vec4(gl_in[idx].gl_Position.xyz * 50.0 + camPos, 1.0);

		EmitVertex();
	}

	EndPrimitive();
}