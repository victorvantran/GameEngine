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
out vec3 wNormal;
out vec3 wFragPos;
out vec3 wLightPos;




// View Space
out vec3 vNormal;
out vec3 vFragPos;
out vec3 vLightPos;




out vec3 tNormal;


/// Texture
out vec2 TexCoord;



void main()
{
	gl_Position = projection * view * model * vec4( aPosition, 1.0f );

	//vFragPos = vec3( view * model * vec4( aPosition, 1.0f ) );
	wFragPos = vec3( model * vec4( aPosition, 1.0f ) );
	wNormal = mat3( transpose( inverse( view * model ) ) ) * aNormal;
	//vLightPos = vec3( view * vec4( vec3( 1.2f, 1.0f, 2.0f ), 1.0 ) );
	wLightPos = vec3( view * vec4( vec3( 1.2f, 1.0f, 2.0f ), 1.0 ) );

	vFragPos = vec3( view * model * vec4( aPosition, 1.0f ) );
	vNormal = normMatrix * aNormal;

	tNormal = mat3( transpose( inverse( model ) ) ) * aNormal;

	TexCoord = aTexCoord;
	return;
}