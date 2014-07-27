#version 430 core

layout(location = 0) in vec3 position;

uniform mat4 shadowMatrix;

out vec2 UV;
out vec4 shadowCoord;

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

void main()
{
	UV = (position.xy + vec2(1,1)) / 2.0;
	gl_Position =  vec4(position,1);
	shadowCoord = shadowMatrix * vec4(position, 1.0);
}

