#version 430 core

in Data
{
	vec3 normal;
	vec3 position;
	vec3 eyePos;
	vec3 lightDir;
	float attenuation;
	vec3 color;
} data;

layout (std140, binding = 10) uniform MaterialDataBlock
{
	vec4 diffuseColor;
	vec4 emissiveColor;
	float metalic;
	float shinyness;
	float roughness;
}materialData;

uniform sampler2D alphaMap;
uniform sampler2D normalMap;

// Ouput data
uniform vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform float lightPower = 100.0;

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 positionColor;
layout (location = 2) out vec4 normalColor;

void main()
{
	vec4 specular = vec4(0.0);
	vec3 normal = normalize(data.normal);
	vec3 eye = normalize(data.eyePos);
	vec3 position = normalize(data.position);
	vec3 lightDir = normalize(data.lightDir);

	float lambert = max(dot(normal, lightDir), 0.0);
	vec4 diffuse = lambert *materialData.diffuseColor;

	if(lambert > 0.0)
	{
		vec3 r =  normalize(reflect(-lightDir, normal));
		float specIntensity = clamp(dot(r, eye), 0.0, 1.0);
		specular = (vec4(1.0) * (1.0 - materialData.metalic) + (materialData.diffuseColor * materialData.metalic)) * pow(specIntensity, 1.0/materialData.shinyness);	
	}

	//fragColor = vec4(materialData.specularColor, 0.0);
	fragColor = (diffuse + specular) * lightPower * data.attenuation;
	normalColor = vec4(normal, 1.0);
	positionColor = vec4(position, 1.0);
}