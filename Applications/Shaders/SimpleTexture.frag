#version 430 core

// Ouput data
layout(location = 0) out vec4 color;

uniform sampler2D tex0;

in vec2 UV;

void main()
{
	color = texture(tex0, UV.xy);
}