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
	Shader _objectShader;
	Shader _lightSourceShader;
	Shader _outlineShader;

	Model _testModel0 = Model( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _testModel1 = Model( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
public:
	TinkerGame() : 
		Game(), 
		_objectShader(),
		_lightSourceShader(),
		_outlineShader()

		//_backpackModel("assets/models/backpack/backpack.obj")
		{}

	~TinkerGame() 
	{
		this->_testModel0.cleanup();
		this->_testModel1.cleanup();
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


		this->_lightSourceShader.load( "assets/shaders/object_vs.shader", "assets/shaders/light_source_fs.shader" );
		this->_objectShader.load( "assets/shaders/object_vs.shader", "assets/shaders/object_fs.shader" );
		this->_outlineShader.load( "assets/shaders/outline_vs.shader", "assets/shaders/outline_fs.shader" );

		//this->_testModel0.load( "assets/models/backpack/backpack.obj" );
		//this->_testModel0.load( "assets/models/pony_cartoon/scene.gltf" );
		//this->_testModel0.load( "assets/models/banana_plant/banana_plant.obj" );
		//this->_testModel0.load( "assets/models/ufo/Low_poly_UFO.obj" );
		//this->_testModel0.load( "assets/models/pizza/scene.obj" );
		//this->_testModel0.load( "assets/models/cube/scene.gltf" );
		//this->_testModel0.load( "assets/models/wooden_crate/scene.obj" );
		this->_testModel0.load( "assets/models/dice/scene.obj" );
		//this->_testModel0.load( "assets/models/suited/scene.obj" );
		//this->_testModel0.load( "assets/models/tree/scene.obj" );


		this->_testModel1.load( "assets/models/cube/scene.gltf" );

		return;
	}




	void update()
	{
		this->processInput();

		return;
	}



	void render()
	{
		this->_screen.clear();

		//// Set up constant matrix projections
		glm::mat4 view = this->_camera.getViewMatrix();
		glm::mat4 projection = glm::perspective( glm::radians( this->_camera.getZoom() ), ( float )this->_screen.getWidth() / ( float )this->_screen.getHeight(), 0.1f, 2000.0f );

		this->_objectShader.use();
		this->_objectShader.setMat4( "view", view );
		this->_objectShader.setMat4( "projection", projection );

		this->_lightSourceShader.use();
		this->_lightSourceShader.setMat4( "view", view );
		this->_lightSourceShader.setMat4( "projection", projection );

		this->_outlineShader.use();
		this->_outlineShader.setMat4( "view", view );
		this->_outlineShader.setMat4( "projection", projection );



		//// Renders before outline
		glStencilMask( 0x00 );

		//// Render SpotLightSourceModel
		this->_lightSourceShader.use();
		glm::mat4 test = glm::mat4( 1.0f );
		test = glm::translate( test, glm::vec3( 2.0f, -10.0f, 2.0f + 0.0f * std::sinf( glfwGetTime() ) ) );
		//test = glm::rotate( test, glm::radians( 45.0f + 45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		test = glm::scale( test, glm::vec3( 50.0f, 0.1f, 50.0f ) );
		this->_lightSourceShader.setMat4( "model", test );
		this->_lightSourceShader.setVec4( "lightColor", glm::vec4(0.2f, 0.2f, 0.2f, 1.0f) );
		this->_testModel1.render( _lightSourceShader );



		//// Renders during outline
		// Discriminate in passing all stencil bits for the upcoming fragments, passing it's origin value by masking with 0xFF
		// Updates the stencil buffer with 1s wherever the object's fragments are rendered
		glStencilFunc( GL_ALWAYS, 1, 0xFF );
		// Enable writes to the stencil buffer
		glStencilMask( 0xFF );

		//// Render TestModel0
		this->_objectShader.use();
		glm::mat4 model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_testModel0.getPosition() );
		model = glm::scale( model, this->_testModel0.getScale() );
		this->_objectShader.setMat4( "model", model );
		glm::mat3 vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_objectShader.setFloat( "material.shininess", 32.0f );

		/// Directional Light
		this->_objectShader.use();
		glm::vec4 directionalLightColor = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
		glm::vec4 directionalLightDiffuse = directionalLightColor * glm::vec4( 0.8f );
		glm::vec4 directionalLightAmbient = directionalLightDiffuse * glm::vec4( 0.0f );
		glm::vec4 directionalLightSpecular = glm::vec4( 1.0f );
		glm::vec3 directionalLightDir = glm::vec3( 0.0f, 0.0f, -1.0f );
		//glm::vec3 directionalLightDir = glm::vec3( 0.0f, -1.0f, 0.0f );
		//glm::vec3 directionalLightDir = glm::vec3( -1.0f, 0.0f, 0.0f );
		glm::mat4 directionalLightModel = glm::mat4( 1.0f );
		directionalLightModel = glm::translate( directionalLightModel, glm::vec3( 0.0f, 0.0f, 0.0f ) );
		glm::vec3 vDirectionalLightDirUnit = glm::normalize( glm::vec3( view * model * glm::vec4( glm::normalize( -directionalLightDir ), 0.0f ) ) );
		this->_objectShader.setVec3( "directionalLight.vDirection", vDirectionalLightDirUnit );
		this->_objectShader.setVec4( "directionalLight.ambient", directionalLightAmbient );
		this->_objectShader.setVec4( "directionalLight.diffuse", directionalLightDiffuse );
		this->_objectShader.setVec4( "directionalLight.specular", directionalLightSpecular );

		/// Point Light 0
		this->_objectShader.use();
		glm::vec4 pointLight0Color = glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f );
		glm::vec4 pointLight0Diffuse = pointLight0Color * glm::vec4( 1.0f );
		glm::vec4 pointLight0Ambient = pointLight0Diffuse * glm::vec4( 0.0f );
		glm::vec4 pointLight0Specular = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
		glm::vec3 pointLight0Pos = glm::vec3( 0.0f, 2.0f, 0.0f );
		glm::vec3 vPointLight0Pos = glm::vec3( view * glm::vec4( pointLight0Pos, 1.0f ) ); // [!] model
		this->_objectShader.setVec3( "pointLights[0].vPosition", vPointLight0Pos );
		this->_objectShader.setVec4( "pointLights[0].ambient", pointLight0Ambient );
		this->_objectShader.setVec4( "pointLights[0].diffuse", pointLight0Diffuse );
		this->_objectShader.setVec4( "pointLights[0].specular", pointLight0Specular );
		this->_objectShader.setFloat( "pointLights[0].kConstant", 1.0f );
		this->_objectShader.setFloat( "pointLights[0].kLinear", 0.09f );
		this->_objectShader.setFloat( "pointLights[0].kQuadratic", 0.032f );

		/// Spot Light 0
		glm::vec4 spotLight0Color = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f );
		glm::vec4 spotLight0Diffuse = spotLight0Color * glm::vec4( 1.0f );
		glm::vec4 spotLight0Ambient = spotLight0Diffuse * glm::vec4( 0.0f );
		glm::vec4 spotLight0Specular = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
		glm::vec3 lSpotLight0Pos = glm::vec3( 0.0f, 0.0f, 0.0f ); // glm::vec3( 2.0f, 0.0f, 2.0f + 0.0f * std::sinf( glfwGetTime() ) );
		glm::vec3 lSpotLight0Dir = glm::vec3( 0.0f, 0.0f, -1.0f );
		// Position
		glm::mat4 spotLight0PosModel = glm::mat4( 1.0f );
		spotLight0PosModel = glm::translate( spotLight0PosModel, glm::vec3( 1.5f, 0.0f, 1.5f + 0.0f * std::sinf( glfwGetTime() ) ) );
		spotLight0PosModel = glm::rotate( spotLight0PosModel, glm::radians( 45.0f + 45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		glm::vec3 vSpotLight0Pos = glm::vec3( view * spotLight0PosModel * glm::vec4( lSpotLight0Pos, 1.0f ) );
		// Direction
		glm::mat4 spotLight0DirModel = glm::mat4( 1.0f );
		spotLight0DirModel = glm::rotate( spotLight0DirModel, glm::radians( 45.0f + 45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		glm::vec3 vSpotLight0Direction = glm::vec3( view * spotLight0DirModel * glm::vec4( lSpotLight0Dir, 0.0f ) );
		// Set uniform
		this->_objectShader.setVec3( "spotLights[0].vPosition", vSpotLight0Pos );
		this->_objectShader.setVec3( "spotLights[0].vDirection", vSpotLight0Direction );
		this->_objectShader.setFloat( "spotLights[0].innerCutOff", glm::cos( glm::radians( 12.5f ) ) );
		this->_objectShader.setFloat( "spotLights[0].outerCutOff", glm::cos( glm::radians( 17.5f ) ) );
		this->_objectShader.setVec4( "spotLights[0].ambient", spotLight0Ambient );
		this->_objectShader.setVec4( "spotLights[0].diffuse", spotLight0Diffuse );
		this->_objectShader.setVec4( "spotLights[0].specular", spotLight0Specular );
		this->_objectShader.setFloat( "spotLights[0].kConstant", 1.0f );
		this->_objectShader.setFloat( "spotLights[0].kLinear", 0.09f );
		this->_objectShader.setFloat( "spotLights[0].kQuadratic", 0.032f );

		this->_testModel0.render( this->_objectShader );
		






		//// Render TestModel0 Outline
		// Discriminate in passing the stencil values that do not equal 1, passing it's origin value by masking with 0xFF
		glStencilFunc( GL_NOTEQUAL, 1, 0xFF );
		// Disable stencil buffer writing
		glStencilMask( 0x00 );
		// Ignore depth test for outline to not allow the "outline effect" to discriminate other fragments in depth testings
		glDisable( GL_DEPTH_TEST );
		this->_outlineShader.use();
		model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_testModel0.getPosition() );
		model = glm::scale( model, this->_testModel0.getScale() );
		this->_outlineShader.setMat4( "model", model );
		this->_outlineShader.setFloat( "scale", 0.52f );
		this->_outlineShader.setVec4( "color", glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f ) );
		this->_testModel0.render( this->_outlineShader );






		//// Renders after outlining
		// Return to stencil normalcy (Enable stencil buffer writing, pass through all values with no modifying, allow for depth testing)
		glStencilMask( 0xFF );
		glStencilFunc( GL_ALWAYS, 0, 0xFF );
		glEnable( GL_DEPTH_TEST );


		//// Render LightSourceModel
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
		this->_lightSourceShader.setVec4( "lightColor", pointLight0Color );
		this->_testModel1.render( _lightSourceShader );



		//// Render SpotLightSourceModel
		this->_lightSourceShader.use();
		glm::mat4 spotLightSource0Model = glm::mat4( 1.0f );
		spotLightSource0Model = glm::translate( spotLightSource0Model, glm::vec3( 1.5f, 0.0f, 1.5f + 0.0f * std::sinf( glfwGetTime() ) ) );
		spotLightSource0Model = glm::rotate( spotLightSource0Model, glm::radians( 45.0f + 45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		spotLightSource0Model = glm::scale( spotLightSource0Model, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", spotLightSource0Model );
		this->_lightSourceShader.setVec4( "lightColor", spotLight0Color );
		this->_testModel1.render( _lightSourceShader );



		this->_screen.newFrame();
		return;
	}

};


#endif