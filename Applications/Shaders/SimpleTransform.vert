#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;

layout (std140, binding = 0) uniform WorldDataBlock
{
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 normalMatrix;
}WorldData;

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

uniform vec3 lightPosition = vec3(0.0, -5.0, 10.0);

void main()
{	
	mat4 MV = WorldData.viewMatrix * WorldData.modelMatrix;
	
	vec3 pos = (MV * vec4(position, 1.0)).xyz;
	vec3 lightPos = (WorldData.viewMatrix * vec4(lightPosition, 1.0)).xyz;

	outData.normal = normalize(mat3(WorldData.normalMatrix) * normal);
	outData.lightDir = normalize(lightPos - pos);
	outData.eyePos = normalize(WorldData.viewMatrix * vec4(-pos, 1.0)).xyz;

	float distance = length(lightPos - pos);
	outData.attenuation = 1.0 / (distance * distance);

	gl_Position =  WorldData.projectionMatrix * MV * vec4(position, 1);
}

