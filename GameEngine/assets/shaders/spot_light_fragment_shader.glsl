#version 330 core


/// Lighting
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light
{
	vec3 wPosition;
	vec3 wDirection;

	vec3 vPosition;

	float cutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float kConstant;
	float kLinear;
	float kQuadratic;
};

uniform Material material;
uniform Light light;


// World
in vec3 wFragPos;

// View
in vec3 vNormal;
in vec3 vFragPos;
in vec3 vLightPos;

out vec4 FragColor;


/// Texture
in vec2 TexCoord;



void main()
{


	// Ambient light
	vec3 ambient = light.ambient * ( vec3( texture( material.diffuse, TexCoord ) ) );

	// Attenuate
	float distance = length( light.wPosition - wFragPos );
	float attenuation = ( 1.0f / ( light.kConstant + light.kLinear * distance + light.kQuadratic * ( distance * distance ) ) );


	// Emission
	vec3 emission = vec3( 1.0f, 1.0f, 1.0f ) * ( vec3( texture( material.emission, TexCoord ) ) );


	// Spot light
	vec3 wLightDir = normalize( light.wPosition - wFragPos );

	float theta = dot( wLightDir, normalize( -light.wDirection ) );
	if ( theta > light.cutOff )
	{

		// Diffuse light
		vec3 norm = normalize( vNormal );
		float diffImpact = max( dot( norm, wLightDir ), 0.0f );
		vec3 diffuse = light.diffuse * ( diffImpact * vec3( texture( material.diffuse, TexCoord ) ) );

		// Specular light
		vec3 viewDir = normalize( -vFragPos );
		vec3 reflectDir = reflect( -wLightDir, norm );
		float specImpact = pow( max( dot( viewDir, reflectDir ), 0.0f ), material.shininess );
		vec3 specular = light.specular * ( specImpact * vec3( texture( material.specular, TexCoord ) ) );

		// Phong Light
		vec3 phongLight = ( ambient + diffuse + specular );

		// Emission
		vec3 emission = vec3( 1.0f, 1.0f, 1.0f ) * ( vec3( texture( material.emission, TexCoord ) ) );

		// Attenuate
		float distance = length( light.vPosition - vFragPos );
		float attenuation = ( 1.0f / ( light.kConstant + light.kLinear * distance + light.kQuadratic * ( distance * distance ) ) );

		FragColor = vec4( phongLight * attenuation + emission, 1.0f );

	}
	else
	{
		// Ambient only
		FragColor = vec4( ambient * attenuation + emission, 1.0f );

	}



	return;

}






/*
#version 330 core


/// Lighting
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light
{
	vec3 vPosition;
	vec3 vDirection;

	float cutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float kConstant;
	float kLinear;
	float kQuadratic;
};

uniform Material material;
uniform Light light;

in vec3 vNormal;
in vec3 vFragPos;
in vec3 vLightPos;

out vec4 FragColor;


/// Texture
in vec2 TexCoord;



void main()
{


	// Ambient light
	vec3 ambient = light.ambient * ( vec3( texture( material.diffuse, TexCoord ) ) );

	// Attenuate
	float distance = length( light.vPosition - vFragPos );
	float attenuation = ( 1.0f / ( light.kConstant + light.kLinear * distance + light.kQuadratic * ( distance * distance ) ) );


	// Emission
	vec3 emission = vec3( 1.0f, 1.0f, 1.0f ) * ( vec3( texture( material.emission, TexCoord ) ) );



	// Spot light
	vec3 vLightDir = normalize( light.vPosition - vFragPos ); // [!] may need to negative
	
	float theta = dot( vLightDir, normalize( -light.vDirection ) );
	if ( theta > light.cutOff )
	{
		
		// Diffuse light
		vec3 norm = normalize( vNormal );
		float diffImpact = max( dot( norm, vLightDir ), 0.0f );
		vec3 diffuse = light.diffuse * ( diffImpact * vec3( texture( material.diffuse, TexCoord ) ) );

		// Specular light
		vec3 viewDir = normalize( -vFragPos );
		vec3 reflectDir = reflect( -vLightDir, norm );
		float specImpact = pow( max( dot( viewDir, reflectDir ), 0.0f ), material.shininess );
		vec3 specular = light.specular * ( specImpact * vec3( texture( material.specular, TexCoord ) ) );

		// Phong Light
		vec3 phongLight = ( ambient + diffuse + specular );

		// Emission
		vec3 emission = vec3( 1.0f, 1.0f, 1.0f ) * ( vec3( texture( material.emission, TexCoord ) ) );

		// Attenuate
		float distance = length( light.vPosition - vFragPos );
		float attenuation = ( 1.0f / ( light.kConstant + light.kLinear * distance + light.kQuadratic * ( distance * distance ) ) );

		FragColor = vec4( phongLight * attenuation + emission, 1.0f );
		//FragColor = vec4( 0.2f );

	}
	else
	{
		// Ambient only
		FragColor = vec4( ambient * attenuation + emission, 1.0f );
		//FragColor = vec4( 0.2f );

	}
	


	return;
	
}
*/