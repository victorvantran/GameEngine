#version 330 core

layout( location = 0 ) in vec3 aPosition;
layout( location = 1 ) in vec3 aNormal;
layout( location = 2 ) in vec2 aTexCoord;
layout( location = 3 ) in mat4 instanceMatrix;


// View Space
out vec3 vNormal;
out vec3 vFragPos;
out vec3 vLightPos;


/// Texture
out vec2 TexCoord;


/// Position
uniform mat4 view;
uniform mat4 projection;



void main()
{	
	//gl_Position = projection * view * model * vec4( aPosition, 1.0f );
	gl_Position = projection * view * instanceMatrix * vec4( aPosition, 1.0f );

	//vNormal = vNormMatrix * aNormal;
	vNormal = mat3( transpose( inverse( view * instanceMatrix ) ) ) * aNormal;

	//vFragPos = vec3( view * model * vec4( aPosition, 1.0f ) );
	vFragPos = vec3( view * instanceMatrix * vec4( aPosition, 1.0f ) );

	TexCoord = aTexCoord;
	return;
}

