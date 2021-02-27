#version 330 core

layout( location = 0 ) in vec3 aPosition;
layout( location = 1 ) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat3 normMatrix;

out vec3 Normal; // normal to the surface 
out vec3 FragPos;


void main()
{
	gl_Position = projection * view * model * vec4( aPosition, 1.0f );
	FragPos = vec3( model * vec4( aPosition, 1.0f ) );
	Normal = normMatrix * aNormal;
	return;
}