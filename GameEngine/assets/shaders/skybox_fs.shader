#version 330 core

in vec3 TexCoord;


out vec4 FragColor;


uniform samplerCube skybox;



void main()
{
	FragColor = texture( skybox, TexCoord );
	//float average = ( FragColor.r + FragColor.g + FragColor.b ) / 3.0;
	//FragColor = vec4( average*0.2, average*0.2, average*0.2, 1.0 );
	return;
}