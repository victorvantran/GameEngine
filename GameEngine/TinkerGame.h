#ifndef TINKER_GAME_H
#define TINKER_GAME_H


#include <cmath>
#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"

class TinkerGame : public Game
{
private:
	Shader _backpackShader;
	Model _backpackModel = Model( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	
	/*
	Model _quint = Model( glm::vec3( 0.0f, 0.0f, 100.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _jon = Model( glm::vec3( 100.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _paul = Model( glm::vec3( 0.0f, 0.0f, -100.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _zeef = Model( glm::vec3( -100.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _daud = Model( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	*/
public:
	TinkerGame() : 
		Game(), 
		_backpackShader()
		//_backpackModel("assets/models/backpack/backpack.obj")
		{}

	~TinkerGame() 
	{
		this->_backpackModel.cleanup();
		/*
		_quint.cleanup();
		_jon.cleanup();
		_paul.cleanup();
		_zeef.cleanup();
		_daud.cleanup();
		*/
	}





	void loadContent()
	{
		stbi_set_flip_vertically_on_load( true );
		glEnable( GL_DEPTH_TEST );

		//this->_backpackShader.load( "assets/shaders/basic_object_vs.shader", "assets/shaders/object_fs.shader" );
		this->_backpackShader.load( "assets/shaders/new_object_vs.shader", "assets/shaders/new_object_fs.shader" );

		//this->_backpackModel.load( "assets/models/backpack/backpack.obj" );
		//this->_backpackModel.load( "assets/models/pony_cartoon/scene.gltf" );
		//this->_backpackModel.load( "assets/models/banana_plant/banana_plant.obj" );
		//this->_backpackModel.load( "assets/models/ufo/Low_poly_UFO.obj" );
		this->_backpackModel.load( "assets/models/cube/scene.gltf" );
		//this->_backpackModel.load( "assets/models/companion_cube/scene.gltf" );
		//this->_quint.load( "assets/models/people/00208_Quint009.obj" );
		//this->_paul.load( "assets/models/people/00218_Jon005.obj" );
		//this->_paul.load( "assets/models/people/00219_Paul008.obj" );
		//this->_zeef.load( "assets/models/people/00246_Zeef006.obj" );
		//this->_daud.load( "assets/models/people/00256_Daud008.obj" );


		return;
	}




	void update()
	{
		this->processInput();

		return;
	}



	void render()
	{
		// Clear the colorbuffer
		glClearColor( 0.8f, 0.8f, 0.8f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


		glm::mat4 view = this->_camera.getViewMatrix();
		glm::mat4 projection = glm::perspective( glm::radians( this->_camera.getZoom() ), ( float )this->_screen.getWidth() / ( float )this->_screen.getHeight(), 0.1f, 2000.0f );

		this->_backpackShader.use();
		this->_backpackShader.setMat4( "view", view );
		this->_backpackShader.setMat4( "projection", projection );

		this->_backpackShader.setVec3( "viewPos", this->_camera.getPosition() );

		
		// Directional Light
		this->_backpackShader.use();
		glm::vec3 directionalLightColor = glm::vec3( 1.0f, 0.0f, 0.0f );
		glm::vec3 directionalLightDiffuse = directionalLightColor * glm::vec3( 0.8f );
		glm::vec3 directionalLightAmbient = directionalLightDiffuse * glm::vec3( 0.0f );
		glm::vec3 directionalLightDir = glm::vec3( 0.0f, 0.0f, -1.0f );
		//glm::vec3 directionalLightDir = glm::vec3( 0.0f, -1.0f, 0.0f );
		//glm::vec3 directionalLightDir = glm::vec3( -1.0f, 0.0f, 0.0f );

		glm::mat4 directionalLightModel = glm::mat4( 1.0f );
		directionalLightModel = glm::translate( directionalLightModel, glm::vec3( 0.0f, 0.0f, 0.0f ) );
		glm::vec3 vDirectionalLightPos = glm::vec3( view * directionalLightModel * glm::vec4( directionalLightDir, 1.0f ) );
		this->_backpackShader.setVec3( "directionalLight.vDirection", vDirectionalLightPos );
		this->_backpackShader.setVec3( "directionalLight.wDirection", directionalLightDir );
		this->_backpackShader.setVec3( "directionalLight.ambient", directionalLightAmbient );
		this->_backpackShader.setVec3( "directionalLight.diffuse", directionalLightDiffuse );
		this->_backpackShader.setVec3( "directionalLight.specular", glm::vec3( 1.0f ) );













		/*
		/// Spot Light 1
		glm::vec3 spotLight1Color = glm::vec3( 1.0f, 0.0f, 1.0f );
		glm::vec3 spotLight1Diffuse = spotLight1Color * glm::vec3( 1.0f );
		glm::vec3 spotLight1Ambient = spotLight1Diffuse * glm::vec3( 0.0f );
		glm::vec3 lSpotLight1Pos = glm::vec3( 0.0f, 0.0f, 0.0f );
		glm::vec3 lSpotLight1Dir = glm::vec3( 0.0f, 0.0f, 1.0f );
		// Position
		glm::mat4 spotLight1PosModel = glm::mat4( 1.0f );
		spotLight1PosModel = glm::translate( spotLight1PosModel, glm::vec3( 0.0f, -10.0f, 0.0f ) );
		spotLight1PosModel = glm::rotate( spotLight1PosModel, glm::radians( 180.0f * -std::sinf( glfwGetTime() ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		glm::vec3 wSpotLight1Pos = glm::vec3( spotLight1PosModel * glm::vec4( lSpotLight1Pos, 1.0f ) );
		glm::vec3 vSpotLight1Pos = glm::vec3( view * spotLight1PosModel * glm::vec4( lSpotLight1Pos, 1.0f ) );
		// Direction
		glm::mat4 spotLight1DirModel = glm::mat4( 1.0f );
		spotLight1DirModel = glm::rotate( spotLight1DirModel, glm::radians( 180.0f * -std::sinf( glfwGetTime() ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		glm::vec3 wSpotLight1Direction = glm::vec3( spotLight1DirModel * glm::vec4( lSpotLight1Dir, 1.0f ) );
		// Set uniform
		this->_backpackShader.setVec3( "spotLights[1].wPosition", wSpotLight1Pos );
		this->_backpackShader.setVec3( "spotLights[1].vPosition", vSpotLight1Pos );
		this->_backpackShader.setVec3( "spotLights[1].wDirection", wSpotLight1Direction );
		this->_backpackShader.setFloat( "spotLights[1].innerCutOff", glm::cos( glm::radians( 12.5f ) ) );
		this->_backpackShader.setFloat( "spotLights[1].outerCutOff", glm::cos( glm::radians( 12.5f ) ) );
		this->_backpackShader.setVec3( "spotLights[1].ambient", spotLight1Ambient );
		this->_backpackShader.setVec3( "spotLights[1].diffuse", spotLight1Diffuse );
		this->_backpackShader.setVec3( "spotLights[1].specular", glm::vec3( 1.0f ) );
		this->_backpackShader.setFloat( "spotLights[1].kConstant", 1.0f );
		this->_backpackShader.setFloat( "spotLights[1].kLinear", 0.09f );
		this->_backpackShader.setFloat( "spotLights[1].kQuadratic", 0.032f );
		*/




		/*
		glm::vec3 offset;

		for ( int i = -100; i < 100; i++ )
		{
			offset = glm::vec3( std::sinf( glfwGetTime() ) * 100.0f + i * 20, 0.0f, std::cosf( glfwGetTime() ) * 100.0f + i * 20 );
			
			this->_quint._position = glm::vec3( 0.0f, 0.0f, 100.0f ) + offset;
			this->_jon._position = glm::vec3( 100.0f, 0.0f, 0.0f ) + offset;
			this->_paul._position = glm::vec3( 0.0f, 0.0f, -100.0f ) + offset;
			this->_zeef._position = glm::vec3( -100.0f, 0.0f, 0.0f ) + offset;
			this->_daud._position = glm::vec3( 0.0f, 0.0f, 0.0f ) + offset;


			this->_quint.render( this->_backpackShader );
			this->_jon.render( this->_backpackShader );
			this->_paul.render( this->_backpackShader );
			this->_zeef.render( this->_backpackShader );
			this->_daud.render( this->_backpackShader );
		}
		*/

		this->_backpackModel.render( this->_backpackShader );



		/*
		// render the loaded model
		glm::mat4 model = glm::mat4( 1.0f );
		model = glm::translate( model, glm::vec3( 0.0f, 0.0f, 0.0f ) ); // translate it down so it's at the center of the scene
		model = glm::scale( model, glm::vec3( 1.0f, 1.0f, 1.0f ) );	// it's a bit too big for our scene, so scale it down
		this->_backpackShader.setMat4( "model", model );
		*/


		// Swap Buffers
		this->_screen.newFrame();
		//glfwSwapBuffers( this->_openGLManager.getWindow() );
		return;
	}


};

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
	vec3 wPosition;

	vec3 vPosition;

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

	// Diffuse light
	vec3 norm = normalize( vNormal );
	//vec3 vLightDir = normalize( light.vPosition - vFragPos );
	vec3 wLightDir = normalize( light.wPosition - wFragPos );

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
	return;
}
*/


#endif