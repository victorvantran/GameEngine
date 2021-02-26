#version 330 core

layout( location = 0 ) in vec3 aPosition;
layout( location = 1 ) in vec4 aColor;
layout( location = 2 ) in vec2 aTexCoord;

out vec4 ourColor;
out vec2 TexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4( aPosition.xyz, 1.0 );
	TexCoord = aTexCoord;
	ourColor = aColor;
	return;
}