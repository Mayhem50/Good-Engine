#version 430 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};

void main(){

    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;

}

