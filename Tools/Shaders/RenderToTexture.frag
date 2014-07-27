#version 430 core

// Ouput data
layout(location = 0) out vec4 color;

uniform sampler2D tex0;
uniform bool linearize;

in vec2 UV;

float linearDepth(float depth)
{
  return (2.0 * 0.01) / (100.0 + 0.01 - depth * (100.0 - 0.01));
}
void main()
{
	if(linearize)
		color = vec4(linearDepth(texture(tex0, UV.xy).r));
	else
		color = texture(tex0, UV.xy);
}