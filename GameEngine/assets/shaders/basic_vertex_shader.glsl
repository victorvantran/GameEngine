#version 330 core

layout( location = 0 ) in vec3 aPosition;
layout( location = 1 ) in vec3 aNormal;
layout( location = 2 ) in vec2 aTexCoord;


/// Position
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


/// Lighting
uniform mat3 normMatrix;

// World Space
out vec3 wFragPos;


// View Space
out vec3 vNormal;
out vec3 vFragPos;
out vec3 vLightPos;

/// Texture
out vec2 TexCoord;



void main()
{
	gl_Position = projection * view * model * vec4( aPosition, 1.0f );

	wFragPos = vec3( model * vec4( aPosition, 1.0f ) );

	vFragPos = vec3( view * model * vec4( aPosition, 1.0f ) );
	vNormal = normMatrix * aNormal;

	TexCoord = aTexCoord;
	return;
}