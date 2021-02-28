#version 330 core

layout( location = 0 ) in vec3 aPosition;
layout( location = 1 ) in vec3 aNormal;
layout( location = 2 ) in vec2 aTexCoord;


/// Position
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


/// Lighting
uniform vec3 lightPos;
uniform mat3 normMatrix;
// View Space
out vec3 vNormal;
out vec3 vFragPos;
out vec3 vLightPos;


/// Texture
out vec2 TexCoord;


void main()
{
	gl_Position = projection * view * model * vec4( aPosition, 1.0f );

	vFragPos = vec3( view * model * vec4( aPosition, 1.0f ) );
	vNormal = normMatrix * aNormal;
	//vNormal = mat3( transpose( inverse( view * model ) ) ) * aNormal;

	vLightPos = vec3( view * vec4( lightPos, 1.0f ) );

	TexCoord = aTexCoord;
	return;
}