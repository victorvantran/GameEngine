#version 330 core

layout( location = 0 ) in vec3 aPosition;
layout( location = 1 ) in vec3 aNormal;
layout( location = 2 ) in vec2 aTexCoord;


/// Position
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float scale;

void main()
{
	gl_Position = projection * view * model * vec4( aPosition + ( aNormal * scale ), 1.0 );
	return;
}