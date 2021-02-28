#version 330 core



// World
in vec3 wFragPos;

// View
in vec3 vNormal;
in vec3 vFragPos;
in vec3 vLightPos;

out vec4 FragColor;



/// Texture
in vec2 TexCoord;



struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

uniform Material material;


/// Lighting



// Directional Light
struct DirectionalLight
{
	vec3 lDirection;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform DirectionalLight directionalLight;

vec3 getDirectionalLight( DirectionalLight directionalLight, vec3 vNormalUnit, vec3 vViewDirUnit )
{
	// Light
	vec3 lLightDirUnit = normalize( -directionalLight.lDirection ); // point TOWARDS light source needed for calculation
	
	// Ambient light
	vec3 ambient = directionalLight.ambient * ( vec3( texture( material.diffuse, TexCoord ) ) );

	// Diffuse light
	float diffImpact = max( dot( vNormalUnit, lLightDirUnit ), 0.0f );
	vec3 diffuse = directionalLight.diffuse * ( diffImpact * vec3( texture( material.diffuse, TexCoord ) ) );

	// Specular light
	vec3 lReflectDir = reflect( -lLightDirUnit, vNormalUnit );
	float specImpact = pow( max( dot( vViewDirUnit, lReflectDir ), 0.0f ), material.shininess );
	vec3 specular = directionalLight.specular * ( specImpact * vec3( texture( material.specular, TexCoord ) ) );

	return ambient + diffuse + specular;
}



// Point Light

struct PointLight
{
	//vec3 wPosition;
	vec3 vPosition;

	float kConstant;
	float kLinear;
	float kQuadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 getPointLight( PointLight pointLight, vec3 vNormalUnit, vec3 vViewDirUnit )
{
	// Light
	vec3 vLightDir = normalize( pointLight.vPosition - vFragPos );

	// Ambient light
	vec3 ambient = pointLight.ambient * ( vec3( texture( material.diffuse, TexCoord ) ) );

	// Diffuse light
	float diffImpact = max( dot( vNormalUnit, vLightDir ), 0.0f );
	vec3 diffuse = pointLight.diffuse * ( diffImpact * vec3( texture( material.diffuse, TexCoord ) ) );

	// Specular light
	vec3 vReflectDir = reflect( -vLightDir, vNormalUnit );
	float specImpact = pow( max( dot( vViewDirUnit, vReflectDir ), 0.0f ), material.shininess );
	vec3 specular = pointLight.specular * ( specImpact * vec3( texture( material.specular, TexCoord ) ) );


	// Attenuate
	float distance = length( pointLight.vPosition - vFragPos );
	float attenuation = ( 1.0f / ( pointLight.kConstant + pointLight.kLinear * distance + pointLight.kQuadratic * ( distance * distance ) ) );

	return ( ambient + diffuse + specular ) * attenuation;
}





void main()
{
	vec3 vNormalUnit = normalize( vNormal );

	vec3 vViewDirUnit = normalize( -vFragPos );

	
	// Directional Lighting
	vec3 cumulativeLight = getDirectionalLight( directionalLight, vNormalUnit, vViewDirUnit );

	// Point Lighting


	// Spot Lighting


	FragColor = vec4( cumulativeLight, 1.0f );
	return;

}


