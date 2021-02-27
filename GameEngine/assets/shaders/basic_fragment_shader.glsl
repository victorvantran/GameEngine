#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};


struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


uniform Material material;
uniform Light light;


in vec3 vNormal;
in vec3 vFragPos;
in vec3 vLightPos;

out vec4 FragColor;


void main()
{
	// Ambient light
	vec3 ambient = light.ambient * material.ambient;


	// Diffuse light
	vec3 norm = normalize( vNormal );
	vec3 lightDir = normalize( vLightPos - vFragPos );
	float diffImpact = max( dot( norm, lightDir ), 0.0f );
	vec3 diffuse = light.diffuse * ( diffImpact * material.diffuse );


	// Specular light
	vec3 viewDir = normalize( -vFragPos );
	vec3 reflectDir = reflect( -lightDir, norm );
	float specImpact = pow( max( dot( viewDir, reflectDir ), 0.0f ), material.shininess );
	vec3 specular = light.specular * ( specImpact * material.specular );


	// Phong Light
	vec3 phongLight = ( ambient + diffuse + specular );

	FragColor = vec4( phongLight, 1.0f );
	return;
}