#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec2 uv;

layout (location = 0) out vec3 outNormal;
layout (location = 1) out vec3 outTangent;
layout (location = 2) out vec3 outBitangent;
layout (location = 3) out vec3 outColor;
layout (location = 4) out vec2 outUV;

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

void main()
{	
	outNormal = normalize(normal);
	outTangent = normalize(tangent);
	outBitangent = normalize(cross(normal, tangent));
	outColor = color;
	outUV = uv;
	gl_Position =  vec4(position, 1.0);
}

