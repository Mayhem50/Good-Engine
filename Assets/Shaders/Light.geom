#version 430 core

layout(triangles, invocations = 1) in;
layout (triangle_strip, max_vertices = 3) out;

layout (location = 0) in vec3 normal[];
layout (location = 1) in vec3 tangent[];
layout (location = 2) in vec3 bitangent[];
layout (location = 3) in vec3 color[];
layout (location = 4) in vec2 uv[];

layout (location = 0) out vec3 outNormal;
layout (location = 1) out vec3 outTangent;
layout (location = 2) out vec3 outBitangent;
layout (location = 3) out vec3 outColor;
layout (location = 4) out vec2 outUv;
layout (location = 5) out vec3 lightDir;
layout (location = 6) out vec3 viewDir;

layout (std140, binding = 0) uniform WorldDataBlock
{
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 normalMatrix;
}worldData;

uniform vec3 lightPosition = vec3(100.0, 100.0, 155.0);

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
	mat4 MV = worldData.viewMatrix * worldData.modelMatrix;
	mat4 MVP =  worldData.projectionMatrix * MV;

	for(int idx = 0; idx < gl_in.length(); ++idx)
	{		
		outNormal = normalize(worldData.normalMatrix * vec4(normal[idx], 0.0)).xyz;
		outTangent = normalize(mat3(worldData.normalMatrix) * tangent[idx]);
		outBitangent = normalize(mat3(worldData.normalMatrix) * bitangent[idx]);
		
		vec3 pos = (MV * gl_in[idx].gl_Position).xyz;
		vec3 lightPos = (worldData.viewMatrix * vec4(lightPosition, 1.0)).xyz;
		
		lightDir = normalize(lightPos - pos);		
		viewDir = normalize(-pos);

		gl_Position = MVP *  gl_in[idx].gl_Position;
		EmitVertex();
	}

	EndPrimitive();
}
