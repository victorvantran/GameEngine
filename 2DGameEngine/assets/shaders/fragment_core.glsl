#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec4 ourColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	//FragColor = texture( texture0, TexCoord );
	//FragColor = texture( texture0, vec2( 1.0f - TexCoord.x, TexCoord.y ) );
	FragColor = mix( texture( texture0, TexCoord ), texture( texture1, TexCoord ), 0.2 ) * ourColor;
	// texture( ourTexture, TexCoord ) * ourColor;  //texture( ourTexture, TexCoord );	//ourColor; //vec4( ( vertexPosition.xyz + 1.0f ) / 2.0f, vertexPosition.w ); //ourColor;
	return;
}