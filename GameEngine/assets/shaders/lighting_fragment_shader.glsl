#version 330 core


// World
in vec3 tNormal;

in vec3 wNormal;
in vec3 wFragPos;
in vec3 wLightPos;


// View
in vec3 vNormal;
in vec3 vFragPos;
in vec3 vLightPos;

out vec4 FragColor;



/// Texture
in vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
in vec3 ANormal;
in vec3 AFragPos;


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
	vec3 vDirection;
	vec3 wDirection;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform DirectionalLight directionalLight;



vec3 getDirectionalLight( DirectionalLight directionalLight, vec3 vNormalUnit, vec3 vViewDirUnit )
{
	// Light
	//vec3 LightPos = vec3( view * vec4( directionalLight.wDirection, 1.0 ) );
	vec3 Normal = ANormal;

	// Ambient light
	vec3 ambient = directionalLight.ambient * ( vec3( texture( material.diffuse, TexCoord ) ) );


	// Diffuse light
	vec3 norm = normalize( Normal );
	//vec3 lightDir = normalize( directionalLight.wDirection - wFragPos );
	vec3 lightDir = normalize( -directionalLight.wDirection );
	float diff = max( dot( norm, lightDir ), 0.0 );
	vec3 diffuse = directionalLight.diffuse * ( diff * vec3( texture( material.diffuse, TexCoord ) ) ); // diff* lightColor;


	// Specular light
	vec3 vLightDirUnit = normalize( directionalLight.vDirection - vFragPos ); // point TOWARDS light source needed for calculation. Therefore, source - frag
	vec3 vReflectDir = reflect( -vLightDirUnit, vNormalUnit );
	float specImpact = pow( max( dot( vViewDirUnit, vReflectDir ), 0.0f ), material.shininess );
	vec3 specular = directionalLight.specular * ( specImpact * vec3( texture( material.specular, TexCoord ) ) );

	return ambient + diffuse + specular;
}


/*
vec3 getDirectionalLight( DirectionalLight directionalLight, vec3 vNormalUnit, vec3 vViewDirUnit )
{
	// Light
	//vec3 LightPos = vec3( view * vec4( directionalLight.wDirection, 1.0 ) );




	vec3 Normal = mat3( transpose( inverse( model ) ) ) * ANormal;
	vec3 Norm = normalize( Normal );
	vec3 LightPos = vec3( vec4( directionalLight.wDirection, 1.0 ) );
	vec3 LightDir = normalize( -LightPos );



	vec3 vNormal = mat3( transpose( inverse( view * model ) ) ) * ANormal;
	vec3 vNorm = normalize( vNormal );

	vec3 vLightPos = vec3(   vec4( directionalLight.wDirection, 1.0 ) );
	vec3 vvFragPos = vec3(    vec4( AFragPos, 1.0 ) );

	//vec3 vLightDir = normalize( -vLightPos );
	vec3 vLightDir = normalize( -(vLightPos - vvFragPos) );
	//vec3 vLightDir = normalize( - vec3( view * vec4( ( LightPos - wFragPos ), 1.0 )) );
	//vec3 vLightDir = normalize( -vec3( view * vec4( ( vec3(0.0f, 0.0f, -1.0f) ), 1.0 ) ) );

	//mat4 norm_matrix = mat4( transpose( inverse( view ) ) );
	//vNorm = normalize( vec3( norm_matrix * vec4( ANormal, 1.0 ) ) );


	//vec3 vLightDir = normalize( vLightPos - vFragPos );

	float diff = max( dot( vNorm, vLightDir ), 0.0 );
	//float diff = max( dot( vNorm, vLightDir ), 0.0 );
	//float diff = max( dot( Norm, LightDir ), 0.0 );
	vec3 diffuse = directionalLight.diffuse * ( diff * vec3( texture( material.diffuse, TexCoord ) ) ); // diff* lightColor;



	return diffuse; // ambient + diffuse + specular;
}
*/



/*
vec3 getDirectionalLight( DirectionalLight directionalLight, vec3 vNormalUnit, vec3 vViewDirUnit )
{
	// Light
	//vec3 LightPos = vec3( view * vec4( directionalLight.wDirection, 1.0 ) );
	vec3 Normal = ANormal;


	// Diffuse light
	vec3 norm = normalize( Normal );
	//vec3 lightDir = normalize( directionalLight.wDirection - wFragPos );
	vec3 lightDir = normalize( -directionalLight.wDirection );
	float diff = max( dot( norm, lightDir ), 0.0 );
	vec3 diffuse = directionalLight.diffuse * ( diff * vec3( texture( material.diffuse, TexCoord ) ) ); // diff* lightColor;


	return diffuse; // ambient + diffuse + specular;
}
*/


/*
vec3 getDirectionalLight( DirectionalLight directionalLight, vec3 vNormalUnit, vec3 vViewDirUnit )
{
	// Light
	vec3 LightPos = vec3( view * vec4( directionalLight.wDirection, 1.0 ) );
	vec3 Normal = mat3( transpose( inverse( view * model ) ) ) * ANormal;


	// Diffuse light
	vec3 norm = normalize( Normal );
	//vec3 lightDir = normalize( LightPos - vFragPos );
	vec3 lightDir = normalize( -LightPos );
	float diff = max( dot( norm, lightDir ), 0.0 );
	vec3 diffuse = directionalLight.diffuse * ( diff * vec3( texture( material.diffuse, TexCoord ) ) ); // diff* lightColor;


	return diffuse; // ambient + diffuse + specular;
}
*/


/*

vec3 getDirectionalLight( DirectionalLight directionalLight, vec3 vNormalUnit, vec3 vViewDirUnit )
{
	// Light
	//vec3 vLightDirUnit = normalize( directionalLight.vDirection - vFragPos ); // point TOWARDS light source needed for calculation. Therefore, source - frag
	//vec3 vLightDirUnit = normalize( directionalLight.wDirection - wFragPos ); // point TOWARDS light source needed for calculation. Therefore, source - frag
	
	//vec3 vLightDirUnit = normalize( -directionalLight.vDirection ); // point TOWARDS light source needed for calculation. Therefore, source - frag
	vec3 vLightDirUnit = normalize( -vec3( view * vec4( directionalLight.vDirection, 1.0 ) ) );

	// Ambient light
	vec3 ambient = directionalLight.ambient * ( vec3( texture( material.diffuse, TexCoord ) ) );

	// Diffuse light
	float diff = max( dot( normalize( mat3( transpose( inverse( view * model ) ) ) * ANormal ), vLightDirUnit ), 0.0 );

	//float diff = max( dot( vNormalUnit, vLightDirUnit ), 0.0 );
	//float diff = max( dot( normalize( tNormal ), vLightDirUnit ), 0.0 );
	vec3 diffuse = directionalLight.diffuse * ( diff * vec3( texture( material.diffuse, TexCoord ) ) ); // diff* lightColor;

	// Specular light
	vec3 vReflectDir = reflect( -vLightDirUnit, vNormalUnit );
	float specImpact = pow( max( dot( vViewDirUnit, vReflectDir ), 0.0f ), material.shininess );
	vec3 specular = directionalLight.specular * ( specImpact * vec3( texture( material.specular, TexCoord ) ) );

	return diffuse; // ambient + diffuse + specular;
}
*/

/*
vec3 getDirectionalLight( DirectionalLight directionalLight, vec3 vNormalUnit, vec3 vViewDirUnit )
{
	// Light
	vec3 wNormalUnit = normalize( wNormal );
	//vec3 vLightDirUnit = normalize( directionalLight.vDirection - vFragPos ); // point TOWARDS light source needed for calculation. Therefore, source - frag
	vec3 wLightDirUnit = normalize( directionalLight.wDirection - wFragPos ); // point TOWARDS light source needed for calculation. Therefore, source - frag


	// Ambient light
	vec3 ambient = directionalLight.ambient * ( vec3( texture( material.diffuse, TexCoord ) ) );

	// Diffuse light
	float diff = max( dot( wNormalUnit, wLightDirUnit ), 0.0 );
	vec3 diffuse = directionalLight.diffuse * ( diff * vec3( texture( material.diffuse, TexCoord ) ) ); // diff* lightColor;

	// Specular light
	vec3  wViewDirUnit = normalize( wViewPos - wFragPos );

	vec3 wReflectDir = reflect( -wLightDirUnit, wNormalUnit );
	float specImpact = pow( max( dot( wViewDirUnit, wReflectDir ), 0.0f ), material.shininess );
	vec3 specular = directionalLight.specular * ( specImpact * vec3( texture( material.specular, TexCoord ) ) );

	return diffuse; // ambient + diffuse + specular;
}
*/


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
	vec3 ambient = pointLight.ambient * ( vec3( texture( material.diffuse, TexCoord ) ) );

	// Diffuse light
	float diffImpact = max( dot( vNormalUnit, vLightDirUnit ), 0.0f );
	vec3 diffuse = pointLight.diffuse * ( diffImpact * vec3( texture( material.diffuse, TexCoord ) ) );

	// Specular light
	vec3 vReflectDir = reflect( -vLightDirUnit, vNormalUnit );
	float specImpact = pow( max( dot( vViewDirUnit, vReflectDir ), 0.0f ), material.shininess );
	vec3 specular = pointLight.specular * ( specImpact * vec3( texture( material.specular, TexCoord ) ) );

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

// uniform SpotLight spotLight;
#define NR_SPOT_LIGHTS 2
uniform SpotLight spotLights[NR_SPOT_LIGHTS];



vec3 getSpotLight( SpotLight spotLight, vec3 vNormalUnit, vec3 vFragPos, vec3 vViewDirUnit )
{
	// Ambient light
	vec3 ambient = spotLight.ambient * ( vec3( texture( material.diffuse, TexCoord ) ) );

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
		vec3 diffuse = spotLight.diffuse * ( diffImpact * vec3( texture( material.diffuse, TexCoord ) ) );
		diffuse *= spotLightIntensity;

		// Specular light
		vec3 vReflectDir = reflect( -vLightDirUnit, vNormalUnit );
		float specImpact = pow( max( dot( vViewDirUnit, vReflectDir ), 0.0f ), material.shininess );
		vec3 specular = spotLight.specular * ( specImpact * vec3( texture( material.specular, TexCoord ) ) );
		specular *= spotLightIntensity;


		// Attenuate
		float distance = length( spotLight.vPosition - vFragPos );
		float attenuation = ( 1.0f / ( spotLight.kConstant + spotLight.kLinear * distance + spotLight.kQuadratic * ( distance * distance ) ) );


		return ( ambient + diffuse + specular );// *attenuation; //diffuse; // ( ambient + diffuse + specular );// *attenuation;
		//return vec3( 1.0f, 1.0f, 0.0f );
	}
	else
	{
		// Ambient only
		return ambient;// *attenuation; //ambient;// *attenuation;
	}
}


void main()
{
	vec3 vNormalUnit = normalize( vNormal );
	vec3 vViewDirUnit = normalize( -vFragPos );

	vec3 cumulativeLight = vec3( 0.0f, 0.0f, 0.0f );

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

	// Emmision Lighting
	vec3 emission = vec3( 1.0f, 1.0f, 1.0f ) * ( vec3( texture( material.emission, TexCoord ) ) );
	cumulativeLight += emission;


	FragColor = vec4( cumulativeLight, 1.0f );
	return;

}
