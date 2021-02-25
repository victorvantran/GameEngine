#version 330 core

out vec4 FragColor;

in vec4 vertexPosition;
in vec4 ourColor;

void main()
{
	FragColor = ourColor; //vec4( ( vertexPosition.xyz + 1.0f ) / 2.0f, vertexPosition.w ); //ourColor;
	return;
}