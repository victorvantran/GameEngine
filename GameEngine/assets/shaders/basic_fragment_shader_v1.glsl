#version 330 core

const float ambientIntensity = 0.05f;
const float specularIntensity = 0.5f;
const int shininess = 32;

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 vNormal;
in vec3 vFragPos;
in vec3 vLightPos;

out vec4 FragColor;


void main()
{
	// Ambient light
	vec3 ambient = vec3( 1.0f, 1.0f, 1.0f ) * ambientIntensity;


	// Diffuse light
	vec3 norm = normalize( vNormal );
	vec3 lightDir = normalize( vLightPos - vFragPos );
	float diffImpact = max( dot( norm, lightDir ), 0.0f );
	vec3 diffuse = diffImpact * lightColor;


	// Specular light
	vec3 viewDir = normalize( -vFragPos );
	vec3 reflectDir = reflect( -lightDir, norm );
	float specMaterialImpact = pow( max( dot( viewDir, reflectDir ), 0.0f ), shininess );
	vec3 specular = specularIntensity * specMaterialImpact * lightColor;


	// Phong Light
	vec3 phongLight = ( ambient + diffuse + specular ) * objectColor;

	FragColor = vec4( phongLight, 1.0f );
	return;
}