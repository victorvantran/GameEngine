#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;


void main()
{
	// Ambient light
	float ambientIntensity = 0.1f;
	vec3 ambient = vec3( 1.0f, 1.0f, 1.0f ) * ambientIntensity;


	// Diffuse light
	vec3 norm = normalize( Normal );
	vec3 lightDir = normalize( lightPos - FragPos );
	float diffImpact = max( dot( norm, lightDir ), 0.0f );
	vec3 diffuse = diffImpact * lightColor;


	// Specular light
	float specularIntensity = 0.5f;
	vec3 viewDir = normalize( viewPos - FragPos );
	vec3 reflectDir = reflect( -lightDir, norm );
	int shininess = 32;
	float specMaterialImpact = pow( max( dot( viewDir, reflectDir ), 0.0f ), shininess );
	vec3 specular = specularIntensity * specMaterialImpact * lightColor;


	// Phong Light
	vec3 phongLight = ( ambient + diffuse + specular ) * objectColor;

	FragColor = vec4( phongLight, 1.0f );
	return;
}