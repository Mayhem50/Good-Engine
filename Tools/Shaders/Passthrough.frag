#version 430 core

layout (location = 0) out vec3 normal;
layout (location = 1) out vec3 tangent;
layout (location = 2) out vec3 bitangent;
layout (location = 3) out vec3 color;
layout (location = 4) out vec2 UV;

out vec4 fragColor;

void main()
{
	fragColor = vec4(color, 1.0);
}