#version 330 core


// World
in vec3 wNormal;
in vec3 wFragPos;


uniform vec3 viewPos;


// View
in vec3 vNormal;
in vec3 vFragPos;

out vec4 FragColor;





/// Texture
in vec2 TexCoord;



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
	vec3 wDirection;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform DirectionalLight directionalLight;

vec3 getDirectionalLight( DirectionalLight directionalLight, vec3 vNormalUnit, vec3 vViewDirUnit )
{
	// Ambient light
	vec3 ambient = directionalLight.ambient * ( vec3( texture( material.diffuse1, TexCoord ) ) );


	// Diffuse light
	vec3 wNormalUnit = normalize( wNormal );
	vec3 wLightDirUnit = normalize( -directionalLight.wDirection );
	float diff = max( dot( wNormalUnit, wLightDirUnit ), 0.0 );
	//vec3 diffuse = directionalLight.diffuse * ( diff * vec3( texture( material.diffuse1, TexCoord ) ) ); // diff* lightColor;
	vec3 diffuse = directionalLight.diffuse * diff ; 


	// Specular light
	vec3 wViewDirUnit = normalize( viewPos - wFragPos );
	vec3 wReflectDir = reflect( -wLightDirUnit, wNormalUnit );
	float specImpact = pow( max( dot( wViewDirUnit, wReflectDir ), 0.0 ), material.shininess );
	//vec3 specular = directionalLight.specular * ( specImpact * vec3( texture( material.specular0, TexCoord ) ) );
	vec3 specular = directionalLight.specular * specImpact;



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

#define NR_POINT_LIGHTS 2
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 getPointLight( PointLight pointLight, vec3 vNormalUnit, vec3 vFragPos, vec3 vViewDirUnit )
{
	// Light
	vec3 vLightDirUnit = normalize( pointLight.vPosition - vFragPos );

	// Ambient light
	vec3 ambient = pointLight.ambient * ( vec3( texture( material.diffuse0, TexCoord ) ) );

	// Diffuse light
	float diffImpact = max( dot( vNormalUnit, vLightDirUnit ), 0.0f );
	vec3 diffuse = pointLight.diffuse * ( diffImpact * vec3( texture( material.diffuse0, TexCoord ) ) );

	// Specular light
	vec3 vReflectDir = reflect( -vLightDirUnit, vNormalUnit );
	float specImpact = pow( max( dot( vViewDirUnit, vReflectDir ), 0.0f ), material.shininess );
	vec3 specular = pointLight.specular * ( specImpact * vec3( texture( material.specular0, TexCoord ) ) );

	// Attenuate
	float distance = length( pointLight.vPosition - vFragPos );
	float attenuation = ( 1.0f / ( pointLight.kConstant + pointLight.kLinear * distance + pointLight.kQuadratic * ( distance * distance ) ) );

	return ( ambient + diffuse + specular ) * attenuation;
}



// Spot Light
struct SpotLight
{
	vec3 wPosition;
	vec3 vPosition;

	vec3 wDirection;


	float innerCutOff;
	float outerCutOff;


	float kConstant;
	float kLinear;
	float kQuadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

#define NR_SPOT_LIGHTS 2
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

vec3 getSpotLight( SpotLight spotLight, vec3 vNormalUnit, vec3 vFragPos, vec3 vViewDirUnit )
{
	// Ambient light
	vec3 ambient = spotLight.ambient * ( vec3( texture( material.diffuse0, TexCoord ) ) );

	// Attenuate
	float distance = length( spotLight.wPosition - wFragPos );
	float attenuation = ( 1.0f / ( spotLight.kConstant + spotLight.kLinear * distance + spotLight.kQuadratic * ( distance * distance ) ) );

	// Spot light
	vec3 wLightDirUnit = normalize( spotLight.wPosition - wFragPos );
	vec3 vLightDirUnit = normalize( spotLight.vPosition - vFragPos );

	float cosTheta = dot( wLightDirUnit, normalize( -spotLight.wDirection ) ); // negate to achieve vector pointing to light source
	float cosEpsilon = spotLight.innerCutOff - spotLight.outerCutOff;
	float spotLightIntensity = clamp( ( cosTheta - spotLight.outerCutOff ) / cosEpsilon, 0.0, 1.0 );

	if ( cosTheta > spotLight.outerCutOff )
	{
		// Diffuse light
		float diffImpact = max( dot( vNormalUnit, vLightDirUnit ), 0.0f );
		vec3 diffuse = spotLight.diffuse * ( diffImpact * vec3( texture( material.diffuse0, TexCoord ) ) );
		diffuse *= spotLightIntensity;

		// Specular light
		vec3 vReflectDir = reflect( -vLightDirUnit, vNormalUnit );
		float specImpact = pow( max( dot( vViewDirUnit, vReflectDir ), 0.0f ), material.shininess );
		vec3 specular = spotLight.specular * ( specImpact * vec3( texture( material.specular0, TexCoord ) ) );
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

	vec3 cumulativeLight = vec3( 0.0f, 0.0f, 0.0f );

	// Directional Lighting
	cumulativeLight += getDirectionalLight( directionalLight, vNormalUnit, vViewDirUnit );



	/*
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

	// Emmision Lighting
	vec3 emission = vec3( 1.0f, 1.0f, 1.0f ) * ( vec3( texture( material.emission, TexCoord ) ) );
	cumulativeLight += emission;
	*/

	FragColor = vec4( cumulativeLight, 1.0f );

	return;

}
