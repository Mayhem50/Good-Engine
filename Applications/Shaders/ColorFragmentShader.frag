#version 430 core

// Interpolated values from the vertex shaders
struct VertexData
{
    vec3 position;
    vec3 color;
    vec3 normal;
    vec2 uv;
};

layout (std140, binding = 10) uniform MaterialDataBlock
{
	vec3 diffuseColor;
	vec3 specularColor;
	vec3 emissiveColor;
	float metalic;
	float roughness;
	float opacity;
	float refraction;
}materialData;
uniform sampler2D alphaMap;
uniform sampler2D normalMap;

layout (std140, binding = 0) uniform WorldDataBlock
{
    mat4 modelMatrix;
    mat4 viewMatrix;
    mat4 projectionMatrix;
	mat4 transposeInverse;
	vec3 camPosition;
}worldData;

in VertexData data;
// Ouput data
layout(location = 0) out vec4 fragColor;
uniform vec3 lightPos = vec3(-5.0, 5.0, 0.0);
uniform vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
uniform float lightPower = 100.0;

vec4 diffuseContribution();
vec4 specularContribution();

void main()
{
	mat4 MV = worldData.viewMatrix * worldData.modelMatrix;
	mat4 MVP = worldData.projectionMatrix * MV;
	mat4 VP = worldData.projectionMatrix * worldData.viewMatrix;

	vec3 normal = normalize(worldData.viewMatrix * worldData.transposeInverse * vec4(data.normal, 1.0)).xyz;
	vec3 lightPosition = (MV * vec4(lightPos, 1.0)).xyz;
	vec3 position = (MV  * vec4(data.position, 1.0)).xyz;

	vec3 lightDirection = normalize(lightPosition - position);
	float lambert = max(0.0, dot(normal, lightDirection));
	vec3 diffuse = lambert * materialData.diffuseColor * lightColor.xyz * lightPower;

	vec3 viewDirection = normalize(vec3(0.0) - position);
	vec3 reflectVector = normalize(reflect(-lightDirection, normal));
	float cosAlpha = dot(reflectVector, viewDirection);
	vec3 specular = pow(clamp(cosAlpha, 0.0, 1.0), 7.5) * materialData.specularColor * lightColor.xyz * lightPower;
	//specular = vec3(cosAlpha, cosAlpha, cosAlpha);
		
    float distance = length(lightPos - data.position);
    //fragColor = lightPower * vec4(materialData.diffuseColor, 0.0) * vec4(diffuse, 0.0) / (distance * distance) ;
    fragColor = vec4(specular, 1.0);// / (distance * distance);
	//fragColor = vec4(data.color, 1.0);
}