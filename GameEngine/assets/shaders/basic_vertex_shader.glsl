#version 330 core

layout( location = 0 ) in vec3 aPosition;
layout( location = 1 ) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
uniform mat3 normMatrix;

// View Space
out vec3 vNormal; // normal to the surface 
out vec3 vFragPos;
out vec3 vLightPos;


void main()
{
	gl_Position = projection * view * model * vec4( aPosition, 1.0f );
	vFragPos = vec3( view * model * vec4( aPosition, 1.0f ) );
	vNormal = normMatrix * aNormal;
	vLightPos = vec3( view * vec4( lightPos, 1.0f ) );
	return;
}