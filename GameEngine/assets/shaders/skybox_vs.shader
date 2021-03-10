#version 330 core

layout( location = 0 ) in vec3 aPosition;
layout( location = 1 ) in vec3 aNormal;
layout( location = 2 ) in vec2 aTexCoord;


out vec3 TexCoord;


/// Position
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()
{
	TexCoord = aPosition;
	gl_Position = projection * view * vec4( aPosition, 1.0 ); 
	return;
}