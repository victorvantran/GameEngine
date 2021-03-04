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
	Shader _lightSourceShader;
	Shader _backpackShader;

	Model _testModel = Model( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _testModel2 = Model( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );

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
		_lightSourceShader(),
		_backpackShader()

		//_backpackModel("assets/models/backpack/backpack.obj")
		{}

	~TinkerGame() 
	{
		this->_testModel.cleanup();
		this->_testModel2.cleanup();
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


		this->_lightSourceShader.load( "assets/shaders/new_object_vs.shader", "assets/shaders/light_source_fs.shader" );
		//this->_lightSourceShader.load( "assets/shaders/new_object_vs.shader", "assets/shaders/new_object_fs.shader" );





		//this->_backpackShader.load( "assets/shaders/basic_object_vs.shader", "assets/shaders/object_fs.shader" );
		this->_backpackShader.load( "assets/shaders/new_object_vs.shader", "assets/shaders/new_object_fs.shader" );
		//this->_backpackShader.load( "assets/shaders/new_object_vs.shader", "assets/shaders/light_source_fs.shader" );


		//this->_backpackModel.load( "assets/models/backpack/backpack.obj" );
		//this->_backpackModel.load( "assets/models/pony_cartoon/scene.gltf" );
		//this->_backpackModel.load( "assets/models/banana_plant/banana_plant.obj" );
		//this->_backpackModel.load( "assets/models/ufo/Low_poly_UFO.obj" );
		this->_testModel.load( "assets/models/cube/scene.gltf" );
		this->_testModel2.load( "assets/models/cube/scene.gltf" );

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
		//glClearColor( 0.8f, 0.8f, 0.8f, 1.0f );
		glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


		glm::mat4 view = this->_camera.getViewMatrix();
		glm::mat4 projection = glm::perspective( glm::radians( this->_camera.getZoom() ), ( float )this->_screen.getWidth() / ( float )this->_screen.getHeight(), 0.1f, 2000.0f );

		this->_backpackShader.use();
		this->_backpackShader.setMat4( "view", view );
		this->_backpackShader.setMat4( "projection", projection );
		this->_backpackShader.setVec3( "viewPos", this->_camera.getPosition() );

		this->_lightSourceShader.use();
		this->_lightSourceShader.setMat4( "view", view );
		this->_lightSourceShader.setMat4( "projection", projection );
		this->_lightSourceShader.setVec3( "viewPos", this->_camera.getPosition() );














		//// TestModel0
		this->_backpackShader.use();
		glm::mat4 model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_testModel.getPosition() );
		model = glm::scale( model, this->_testModel.getScale() );
		this->_backpackShader.setMat4( "model", model );

		glm::mat3 vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_backpackShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_backpackShader.setFloat( "material.shininess", 32.0f );

		
		/// Directional Light
		this->_backpackShader.use();
		glm::vec3 directionalLightColor = glm::vec3( 1.0f, 0.0f, 0.0f );
		glm::vec3 directionalLightDiffuse = directionalLightColor * glm::vec3( 0.8f );
		glm::vec3 directionalLightAmbient = directionalLightDiffuse * glm::vec3( 0.0f );
		glm::vec3 directionalLightDir = glm::vec3( 0.0f, 0.0f, -1.0f );
		//glm::vec3 directionalLightDir = glm::vec3( 0.0f, -1.0f, 0.0f );
		//glm::vec3 directionalLightDir = glm::vec3( -1.0f, 0.0f, 0.0f );
		glm::mat4 directionalLightModel = glm::mat4( 1.0f );
		directionalLightModel = glm::translate( directionalLightModel, glm::vec3( 0.0f, 0.0f, 0.0f ) );
		glm::vec3 vDirectionalLightDirUnit = glm::normalize( glm::vec3( view * model * glm::vec4( glm::normalize( -directionalLightDir ), 0.0f ) ) );
		this->_backpackShader.setVec3( "directionalLight.vDirection", vDirectionalLightDirUnit );
		this->_backpackShader.setVec3( "directionalLight.wDirection", directionalLightDir );
		this->_backpackShader.setVec3( "directionalLight.ambient", directionalLightAmbient );
		this->_backpackShader.setVec3( "directionalLight.diffuse", directionalLightDiffuse );
		this->_backpackShader.setVec3( "directionalLight.specular", glm::vec3( 1.0f ) );


		/// Point Light 0
		this->_backpackShader.use();
		glm::vec3 pointLight0Color = glm::vec3( 0.0f, 1.0f, 0.0f );
		glm::vec3 pointLight0Diffuse = pointLight0Color * glm::vec3( 0.8f );
		glm::vec3 pointLight0Ambient = pointLight0Diffuse * glm::vec3( 0.0f );
		glm::vec3 pointLight0Pos = glm::vec3( 0.0f, 5.0f, 0.0f );
		//glm::vec3 pointLight0Pos = glm::vec3( 0.0f, 0.0f, 0.0f );
		glm::vec3 vPointLight0Pos = glm::vec3( view * glm::vec4( pointLight0Pos, 1.0f ) ); // [!] model
		this->_backpackShader.setVec3( "pointLights[0].vPosition", vPointLight0Pos );
		this->_backpackShader.setVec3( "pointLights[0].ambient", pointLight0Ambient );
		this->_backpackShader.setVec3( "pointLights[0].diffuse", pointLight0Diffuse );
		this->_backpackShader.setVec3( "pointLights[0].specular", glm::vec3( 1.0f ) );
		this->_backpackShader.setFloat( "pointLights[0].kConstant", 1.0f );
		this->_backpackShader.setFloat( "pointLights[0].kLinear", 0.09f );
		this->_backpackShader.setFloat( "pointLights[0].kQuadratic", 0.032f );


		/*
		/// Spot Light 0
		glm::vec3 spotLight0Color = glm::vec3( 1.0f, 0.0f, 1.0f );
		glm::vec3 spotLight0Diffuse = spotLight0Color * glm::vec3( 1.0f );
		glm::vec3 spotLight0Ambient = spotLight0Diffuse * glm::vec3( 0.0f );
		glm::vec3 lSpotLight0Pos = glm::vec3( 0.0f, 0.0f, 0.0f );
		glm::vec3 lSpotLight0Dir = glm::vec3( 0.0f, 0.0f, -1.0f );
		// Position
		glm::mat4 spotLight0PosModel = glm::mat4( 1.0f );
		spotLight0PosModel = glm::translate( spotLight0PosModel, glm::vec3( 2.0f, 0.0f, 2.0f + 0.0f * std::sinf( glfwGetTime() ) ) );
		spotLight0PosModel = glm::rotate( spotLight0PosModel, glm::radians( -25.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ) );

		spotLight0PosModel = glm::rotate( spotLight0PosModel, glm::radians( 45.0f +  45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );

		glm::vec3 wSpotLight0Pos = glm::vec3( spotLight0PosModel * glm::vec4( lSpotLight0Pos, 1.0f ) );
		glm::vec3 vSpotLight0Pos = glm::vec3( view * spotLight0PosModel * glm::vec4( lSpotLight0Pos, 1.0f ) );

		// Direction
		glm::mat4 spotLight0DirModel = glm::mat4( 1.0f );
		spotLight0DirModel = glm::rotate( spotLight0DirModel, glm::radians( 45.0f + 45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );

		glm::vec3 wSpotLight0Direction = glm::vec3( spotLight0DirModel * glm::vec4( lSpotLight0Dir, 1.0f ) );
		// Set uniform
		this->_backpackShader.setVec3( "spotLights[0].wPosition", wSpotLight0Pos );
		this->_backpackShader.setVec3( "spotLights[0].vPosition", vSpotLight0Pos );
		this->_backpackShader.setVec3( "spotLights[0].wDirection", wSpotLight0Direction );
		this->_backpackShader.setFloat( "spotLights[0].innerCutOff", glm::cos( glm::radians( 12.5f ) ) );
		this->_backpackShader.setFloat( "spotLights[0].outerCutOff", glm::cos( glm::radians( 17.5f ) ) );
		this->_backpackShader.setVec3( "spotLights[0].ambient", spotLight0Ambient );
		this->_backpackShader.setVec3( "spotLights[0].diffuse", spotLight0Diffuse );
		this->_backpackShader.setVec3( "spotLights[0].specular", glm::vec3( 1.0f ) );
		this->_backpackShader.setFloat( "spotLights[0].kConstant", 1.0f );
		this->_backpackShader.setFloat( "spotLights[0].kLinear", 0.09f );
		this->_backpackShader.setFloat( "spotLights[0].kQuadratic", 0.032f );
		*/


	
		/// Spot Light 0
		glm::vec3 spotLight0Color = glm::vec3( 1.0f, 0.0f, 1.0f );
		glm::vec3 spotLight0Diffuse = spotLight0Color * glm::vec3( 1.0f );
		glm::vec3 spotLight0Ambient = spotLight0Diffuse * glm::vec3( 0.0f );
		glm::vec3 lSpotLight0Pos = glm::vec3( 0.0f, 0.0f, 0.0f ); // glm::vec3( 2.0f, 0.0f, 2.0f + 0.0f * std::sinf( glfwGetTime() ) );
		glm::vec3 lSpotLight0Dir = glm::vec3( 0.0f, 0.0f, -1.0f );
		// Position
		glm::mat4 spotLight0PosModel = glm::mat4( 1.0f );
		spotLight0PosModel = glm::translate( spotLight0PosModel, glm::vec3( 2.0f, 0.0f, 2.0f + 0.0f * std::sinf( glfwGetTime() ) ) );
		spotLight0PosModel = glm::rotate( spotLight0PosModel, glm::radians( 45.0f + 45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );

		glm::vec3 wSpotLight0Pos = glm::vec3( spotLight0PosModel * glm::vec4( lSpotLight0Pos, 1.0f ) );
		// glm::vec3 vSpotLight0Pos = glm::vec3( view * spotLight0PosModel * glm::vec4( lSpotLight0Pos, 1.0f ) );
		//glm::vec3 vSpotLight0Pos = glm::normalize( glm::vec3( view * glm::vec4( lSpotLight0Pos, 1.0f ) ) );
		glm::vec3 vSpotLight0Pos = glm::vec3( view * spotLight0PosModel * glm::vec4( lSpotLight0Pos, 1.0f ) );


		// Direction
		glm::mat4 spotLight0DirModel = glm::mat4( 1.0f );
		//spotLight0DirModel = glm::translate( spotLight0DirModel, glm::vec3( 2.0f, 0.0f, 2.0f + 0.0f * std::sinf( glfwGetTime() ) ) );
		spotLight0DirModel = glm::rotate( spotLight0DirModel, glm::radians( 45.0f + 45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );


		glm::vec3 wSpotLight0Direction = glm::vec3( spotLight0DirModel * glm::vec4( lSpotLight0Dir, 0.0f ) );
		//glm::vec3 vSpotLight0Direction = glm::vec3( view * spotLight0DirModel * glm::vec4( lSpotLight0Dir, 0.0f ) );
		//glm::vec3 vSpotLight0Direction = glm::normalize( glm::vec3( view * spotLight0PosModel * glm::vec4( glm::normalize( lSpotLight0Pos + lSpotLight0Dir ), 0.0f ) ) );
		//glm::vec3 vSpotLight0Direction = glm::normalize( glm::vec3( view * spotLight0DirModel * glm::vec4( glm::normalize( lSpotLight0Dir ), 0.0f ) ) );
		//glm::vec3 vSpotLight0Direction = glm::vec3( view * spotLight0DirModel * glm::vec4( glm::normalize( lSpotLight0Dir ), 0.0f ) );
		glm::vec3 vSpotLight0Direction = glm::vec3( view * spotLight0DirModel * glm::vec4( lSpotLight0Dir, 0.0f ) );

		// Set uniform
		this->_backpackShader.setVec3( "spotLights[0].wPosition", wSpotLight0Pos );
		this->_backpackShader.setVec3( "spotLights[0].vPosition", vSpotLight0Pos );
		this->_backpackShader.setVec3( "spotLights[0].wDirection", wSpotLight0Direction );
		this->_backpackShader.setVec3( "spotLights[0].vDirection", vSpotLight0Direction );
		this->_backpackShader.setFloat( "spotLights[0].innerCutOff", glm::cos( glm::radians( 12.5f ) ) );
		this->_backpackShader.setFloat( "spotLights[0].outerCutOff", glm::cos( glm::radians( 17.5f ) ) );
		this->_backpackShader.setVec3( "spotLights[0].ambient", spotLight0Ambient );
		this->_backpackShader.setVec3( "spotLights[0].diffuse", spotLight0Diffuse );
		this->_backpackShader.setVec3( "spotLights[0].specular", glm::vec3( 1.0f ) );
		this->_backpackShader.setFloat( "spotLights[0].kConstant", 1.0f );
		this->_backpackShader.setFloat( "spotLights[0].kLinear", 0.09f );
		this->_backpackShader.setFloat( "spotLights[0].kQuadratic", 0.032f );






		this->_testModel.render( this->_backpackShader );
		







		//// LightSourceModel
		this->_lightSourceShader.use();
		glm::vec3 pointLightSource0Pos = pointLight0Pos;
		glm::mat4 pointLightSource0Model = glm::mat4( 1.0f );
		pointLightSource0Model = glm::translate( pointLightSource0Model, pointLightSource0Pos );
		pointLightSource0Model = glm::scale( pointLightSource0Model, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", pointLightSource0Model );

		vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * pointLightSource0Model ) ) );
		this->_lightSourceShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_lightSourceShader.setFloat( "material.shininess", 32.0f );


		this->_lightSourceShader.setVec3( "lightColor", pointLight0Color );

		this->_testModel.render( _lightSourceShader );







		/// SpotLightSourceModel
		this->_lightSourceShader.use();
		glm::mat4 spotLightSource0Model = glm::mat4( 1.0f );
		spotLightSource0Model = glm::translate( spotLightSource0Model, glm::vec3( 2.0f, 0.0f, 2.0f + 0.0f * std::sinf( glfwGetTime() ) ) );
		spotLightSource0Model = glm::rotate( spotLightSource0Model, glm::radians( 45.0f + 45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		spotLightSource0Model = glm::scale( spotLightSource0Model, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", spotLightSource0Model );
		this->_lightSourceShader.setVec3( "lightColor", spotLight0Color );
		this->_testModel.render( _lightSourceShader );


		/*
		this->_lightSourceShader.use();
		glm::vec3 pointLightSource0Pos = pointLight0Pos;
		glm::mat4 pointLightSource0Model = glm::mat4( 1.0f );
		pointLightSource0Model = glm::translate( pointLightSource0Model, pointLightSource0Pos );
		pointLightSource0Model = glm::scale( pointLightSource0Model, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", pointLightSource0Model );

		vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * pointLightSource0Model ) ) );
		this->_lightSourceShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_lightSourceShader.setFloat( "material.shininess", 32.0f );


		this->_lightSourceShader.setVec3( "lightColor", pointLight0Color );

		this->_testModel.render( _lightSourceShader );
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