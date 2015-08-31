#version 430 core

// In variables
const float PI = 3.14159265358979323846264;
const float EPSILON = 0.00000000001;

layout (location = 0) in vec3 normal;
layout (location = 1) in vec3 tangent;
layout (location = 2) in vec3 bitangent;
layout (location = 3) in vec3 color;
layout (location = 4) in vec2 uv;
layout (location = 5) in vec3 lightDir;
layout (location = 6) in vec3 viewDir;

uniform sampler2D alphaMap;
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform samplerCube environementCubeMap;

// Uniforms
layout (std140, binding = 10) uniform MaterialDataBlock
{
	vec4 diffuseColor;
	vec4 specularColor;
	vec4 emissiveColor;	
	float roughness;
	float metallic;
	float opacity;
	float indice;
}materialData;


layout (std140, binding = 1) uniform LightBlock
{
	vec4 lightColor;
};

subroutine vec4 ComputeDiffuseColor();
subroutine (ComputeDiffuseColor)
vec4 ComputeDiffuseColorWithoutTexutre()
{
		
}

float diffuseCoefficient(vec3 normal, vec3 lightDir)
{			
	return  max(dot(normal, lightDir), 0.0) / PI;
}

float specularCoefficient(vec3 viewDir, vec3 normal, vec3 lightDir)
{
	float roughness = materialData.roughness;
	float alpha = roughness * roughness;
	float k = pow((roughness + 1.0), 2) / 8.0;
	vec3 H = normalize(lightDir + viewDir);
	
	return pow(max(dot(normal, H), 0.0), 350);

	/*float NdotV = max(dot(normal, viewDir), 0.0);
	float NdotL = max(dot(normal, lightDir), 0.0);
	float NdotH = max(dot(normal, H), 0.0);
	float VdotH = max(dot(viewDir, H), 0.0);
	float LdotH = max(dot(lightDir, H), 0.0);
	
	float D = alpha * alpha / ( PI * pow((pow(NdotH, 2) * ( alpha * alpha - 1.0) + 1), 2));
	
	float Gv = NdotV / (NdotV * (1.0 - k) + k);
	float Gl = NdotL / (NdotL * (1.0 - k) + k);
	float G = Gv * Gl;
	
	float F0 = 0.5 + 2 * VdotH * VdotH * roughness;
	float exponent = -5.55473 * VdotH - 6.98316 * VdotH;
	float F = F0 + (1.0 - F0) * pow(2.0, exponent);
	
	float denum = max(4.0 * NdotL * NdotV, EPSILON);
	
	return D * G * F / denum;*/
}

layout (location = 0) out vec4 fragColor;
layout (location = 1) out vec4 outDiffuseColor;
layout (location = 2) out vec4 outSpecularColor;
layout (location = 3) out vec4 normalColor;

void main()
{
	vec3 normal = normalize(normal);
	vec3 viewDir = normalize(viewDir);
	vec3 lightDir = normalize(lightDir);
	
	float diffuseFactor =  diffuseCoefficient(normal, lightDir);
	float specularFactor = materialData.specularColor * specularCoefficient(viewDir, normal, lightDir);
	
	vec3 R = normalize(reflect(viewDir, normal));
	vec4 envColor = texture(environementCubeMap, vec3(R.x, -R.yz));

	outDiffuseColor = vec4(viewDir, 1.0);//materialData.diffuseColor * diffuseFactor;
	outSpecularColor = vec4(lightDir, 1.0);//materialData.specularColor * specularFactor;
	normalColor = vec4(normal, 1.0);
	fragColor = ((1.0 - materialData.metallic) * materialData.diffuseColor  * diffuseFactor + materialData.specularColor * specularFactor);
}