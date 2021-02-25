#version 330 core

layout( location = 0 ) in vec3 aPosition;
layout( location = 1 ) in vec4 aColor;


out vec4 vertexPosition;
out vec4 ourColor;

uniform float xOffset;

void main()
{
	/*
	gl_Position = vec4( aPosition.x + xOffset, aPosition.yz, 1.0 );
	vertexPosition = gl_Position;
	ourColor = aColor;
	*/
	gl_Position = vec4( aPosition.xyz, 1.0 );
	ourColor = aColor;
	return;
}