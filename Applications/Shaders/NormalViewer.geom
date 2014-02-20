#version 430 core

layout(triangles) in;
layout (line_strip, max_vertices = 6) out;

in vec3 normal[];

out Data
{
	vec3 normal;
	vec3 eyePos;
	vec3 lightDir;
	float attenuation;
	vec3 color;
} outData;

layout (std140, binding = 0) uniform WorldDataBlock
{
	mat4 modelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 normalMatrix;
}worldData;

uniform vec3 lightPosition = vec3(0.0, -5.0, 10.0);

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
		vec3 pos = (MV * gl_in[idx].gl_Position).xyz;
		vec3 lightPos = (worldData.viewMatrix * vec4(lightPosition, 1.0)).xyz;

		outData.normal = normalize(mat3(worldData.normalMatrix) * normal[idx]);
		outData.lightDir = normalize(lightPos - pos);
		outData.eyePos = normalize(worldData.viewMatrix * vec4(-pos, 1.0)).xyz;

		float distance = length(lightPos - pos);
		outData.attenuation = 1.0 / (distance * distance);

		gl_Position = MVP *  gl_in[idx].gl_Position;
		EmitVertex();
		
		gl_Position = MVP * vec4(gl_in[idx].gl_Position.xyz + normal[idx] * .2, 1.0);
		EmitVertex();

		EndPrimitive();
	}

}
