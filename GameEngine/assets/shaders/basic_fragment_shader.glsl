#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;


void main()
{
	// Ambient light
	float ambientMagnitude = 0.1f;
	vec3 ambient = vec3( 1.0f, 1.0f, 1.0f ) * ambientMagnitude;

	// Diffuse light
	vec3 norm = normalize( Normal );
	vec3 lightDir = normalize( lightPos - FragPos );
	float diffImpact = max( dot( norm, lightDir ), 0.0f );
	vec3 diffuse = diffImpact * lightColor;

	vec3 phongLight = ( ambient + diffuse ) * objectColor;

	FragColor = vec4( phongLight, 1.0f );
	return;
}