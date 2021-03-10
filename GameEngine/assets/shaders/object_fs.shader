#version 330 core

// View Space
in vec3 vNormal;
in vec3 vFragPos;

/// Texture
in vec2 TexCoord;


out vec4 FragColor;


struct Material
{
	sampler2D diffuse0;
	sampler2D diffuse1;
	sampler2D diffuse2;
	sampler2D diffuse3;
	sampler2D specular0;
	sampler2D specular1;
	sampler2D specular2;
	sampler2D specular3;

	sampler2D emission;
	float shininess;
};

uniform Material material;


/// Lighting
// Directional Light
struct DirectionalLight
{
	vec3 vDirection;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

uniform DirectionalLight directionalLight;

vec4 getDirectionalLight( DirectionalLight directionalLight, vec3 vNormalUnit, vec3 vViewDirUnit )
{
	// Ambient light
	vec4 ambient = directionalLight.ambient * texture( material.diffuse0, TexCoord );

	// Diffuse light
	float diffImpact = max( dot( vNormalUnit, directionalLight.vDirection ), 0.0 );
	vec4 diffuse = ( directionalLight.diffuse * diffImpact ) * texture( material.diffuse0, TexCoord );
	
	// Specular light
	vec3 vReflectDir = reflect( -directionalLight.vDirection, vNormalUnit );
	float specImpact = pow( max( dot( vViewDirUnit, vReflectDir ), 0.0 ), material.shininess );
	vec4 specular = ( directionalLight.specular *  specImpact ) * texture( material.diffuse0, TexCoord );
	
	return ambient + diffuse + specular;
}



// Point Light
struct PointLight
{
	vec3 vPosition;

	float kConstant;
	float kLinear;
	float kQuadratic;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

#define NR_POINT_LIGHTS 1
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec4 getPointLight( PointLight pointLight, vec3 vNormalUnit, vec3 vFragPos, vec3 vViewDirUnit )
{
	// Attenuation
	float distance = length( pointLight.vPosition - vFragPos );
	float attenuation = ( 1.0f / ( pointLight.kConstant + pointLight.kLinear * distance + pointLight.kQuadratic * ( distance * distance ) ) );

	// Light Ray
	vec3 vLightDirUnit = normalize( pointLight.vPosition - vFragPos );

	// Ambient light
	vec4 ambient = pointLight.ambient * texture( material.diffuse0, TexCoord );

	// Diffuse light
	float diffImpact = max( dot( vNormalUnit, vLightDirUnit ), 0.0f );
	vec4 diffuse = ( pointLight.diffuse * diffImpact ) * texture( material.diffuse0, TexCoord );

	// Specular light
	vec3 vReflectDir = reflect( -vLightDirUnit, vNormalUnit );
	float specImpact = pow( max( dot( vViewDirUnit, vReflectDir ), 0.0f ), material.shininess );
	vec4 specular = ( pointLight.specular * specImpact ) * texture( material.diffuse0, TexCoord );

	return ( ambient + diffuse + specular ) * attenuation;
}



// Spot Light
struct SpotLight
{
	vec3 vPosition;
	vec3 vDirection;

	float innerCutOff;
	float outerCutOff;

	float kConstant;
	float kLinear;
	float kQuadratic;

	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

#define NR_SPOT_LIGHTS 1
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

vec4 getSpotLight( SpotLight spotLight, vec3 vNormalUnit, vec3 vFragPos, vec3 vViewDirUnit )
{
	// Attenuation
	float distance = length( spotLight.vPosition - vFragPos );
	float attenuation = ( 1.0f / ( spotLight.kConstant + spotLight.kLinear * distance + spotLight.kQuadratic * ( distance * distance ) ) );

	// Light Ray
	vec3 vLightDirUnit = normalize( spotLight.vPosition - vFragPos );

	// Ambient light
	vec4 ambient = spotLight.ambient * texture( material.diffuse0, TexCoord );

	float cosTheta = dot( vLightDirUnit, normalize( -spotLight.vDirection ) ); // negate to achieve vector pointing to light source
	float cosEpsilon = spotLight.innerCutOff - spotLight.outerCutOff;
	float spotLightIntensity = clamp( ( cosTheta - spotLight.outerCutOff ) / cosEpsilon, 0.0, 1.0 );

	if ( cosTheta > spotLight.outerCutOff )
	{
		// Diffuse light
		float diffImpact = max( dot( vNormalUnit, vLightDirUnit ), 0.0f );
		vec4 diffuse = ( spotLight.diffuse * diffImpact ) * texture( material.diffuse0, TexCoord );
		diffuse *= spotLightIntensity;

		// Specular light
		vec3 vReflectDir = reflect( -vLightDirUnit, vNormalUnit );
		float specImpact = pow( max( dot( vViewDirUnit, vReflectDir ), 0.0f ), material.shininess );
		vec4 specular = ( spotLight.specular * specImpact ) * texture( material.specular0, TexCoord );

		specular *= spotLightIntensity;

		return ( ambient + diffuse + specular ) * attenuation;
	}
	else
	{
		// Ambient only ( or no light )
		return ambient * attenuation;
	}
}





void main()
{
	
	vec3 vNormalUnit = normalize( vNormal );
	vec3 vViewDirUnit = normalize( -vFragPos );

	vec4 cumulativeLight = vec4( 0.0f, 0.0f, 0.0f, 0.0f );

	// Directional Lighting
	cumulativeLight += getDirectionalLight( directionalLight, vNormalUnit, vViewDirUnit );

	// Point Lighting
	for ( int i = 0; i < NR_POINT_LIGHTS; i++ )
	{
		cumulativeLight += getPointLight( pointLights[i], vNormalUnit, vFragPos, vViewDirUnit );
	}

	
	// Spot Lighting
	for ( int i = 0; i < NR_SPOT_LIGHTS; i++ )
	{
		cumulativeLight += getSpotLight( spotLights[i], vNormalUnit, vFragPos, vViewDirUnit );
	}

	// Emission Lighting
	//vec3 emission = vec3( 1.0f, 1.0f, 1.0f ) * ( vec3( texture( material.emission, TexCoord ) ) );
	//cumulativeLight += emission;


	FragColor = cumulativeLight;


	//float average = ( FragColor.r + FragColor.g + FragColor.b ) / 3.0;
	//FragColor = vec4( average, average, average, 1.0 );
	return;

}
