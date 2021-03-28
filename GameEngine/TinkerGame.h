#ifndef TINKER_GAME_H
#define TINKER_GAME_H


#include <cmath>
#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "ModelArray.h"
#include "WoodenChair.h"

class TinkerGame : public Game
{
private:
	Shader _objectShader;
	Shader _objectInstancedShader;
	Shader _lightSourceShader;
	Shader _outlineShader;
	Shader _skyboxShader;

	Model _skyModel0 = Model( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );

	ModelArray _testModelArray = ModelArray( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	
	/*
	Model _testModel0 = Model( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _testModel1 = Model( glm::vec3( 2.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _chairYellowModel = Model( glm::vec3( 4.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _toiletModel = Model( glm::vec3( 6.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _squareStoolModel = Model( glm::vec3( 8.0f, 0.0f, 0.0f ), glm::vec3( 0.001f, 0.001f, 0.001f ) );
	Model _ottomanModel = Model( glm::vec3( 10.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );
	Model _wickerModel = Model( glm::vec3( 12.0f, 0.0f, 0.0f ), glm::vec3( 0.001f, 0.001f, 0.001f ) );
	Model _checkerModel = Model( glm::vec3( 14.0f, 0.0f, 0.0f ), glm::vec3( 0.01f, 0.01f, 0.01f ) );
	Model _schoolModel = Model( glm::vec3( 16.0f, 0.0f, 0.0f ), glm::vec3( 0.25f, 0.25f, 0.25f ) );
	*/

	WoodenChair _woodenChair = WoodenChair( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 1.0f, 1.0f, 1.0f ) );



	GLuint _cubeMapTextureId;


	unsigned int amount = 1000;
	glm::mat4* modelMatrices = new glm::mat4[amount];


public:
	TinkerGame() : 
		Game(), 
		_objectShader(),
		_lightSourceShader(),
		_outlineShader(),
		_cubeMapTextureId( 0 )
		{}

	~TinkerGame() 
	{
		
		this->_skyModel0.cleanup();
		this->_woodenChair.cleanup();
		/*
		this->_testModel0.cleanup();
		this->_testModel1.cleanup();
		this->_chairYellowModel.cleanup();
		this->_toiletModel.cleanup();
		this->_squareStoolModel.cleanup();
		this->_ottomanModel.cleanup();
		this->_wickerModel.cleanup();
		this->_checkerModel.cleanup();
		this->_schoolModel.cleanup();
		*/

		glDeleteTextures( 1, &this->_cubeMapTextureId );
	}





	void loadContent()
	{
		stbi_set_flip_vertically_on_load( true );

		this->_lightSourceShader.createShaderProgram( "assets/shaders/object_vs.shader", "assets/shaders/light_source_fs.shader" );

		this->_objectShader.createShaderProgram( "assets/shaders/object_vs.shader", "assets/shaders/object_fs.shader" );
		this->_objectInstancedShader.createShaderProgram( "assets/shaders/object_instanced_vs.shader", "assets/shaders/object_fs.shader" );
		//this->_objectInstancedShader.createShaderProgram( "assets/shaders/object_vs.shader", "assets/shaders/object_fs.shader" );


		this->_outlineShader.createShaderProgram( "assets/shaders/outline_vs.shader", "assets/shaders/outline_fs.shader" );
		this->_skyboxShader.createShaderProgram( "assets/shaders/skybox_vs.shader", "assets/shaders/skybox_fs.shader" );


		this->_skyModel0.load( "assets/models/dice/scene.obj" );


		//this->_testModel0.load( "assets/models/backpack/backpack.obj" );
		//this->_testModel0.load( "assets/models/pony_cartoon/scene.gltf" );
		//this->_testModel0.load( "assets/models/banana_plant/banana_plant.obj" );
		//this->_testModel0.load( "assets/models/ufo/Low_poly_UFO.obj" );
		//this->_testModel0.load( "assets/models/pizza/scene.obj" );
		//this->_testModel0.load( "assets/models/cube/scene.gltf" );
		//this->_testModel0.load( "assets/models/wooden_crate/scene.obj" );
		//this->_testModel0.load( "assets/models/dice/scene.obj" );
		//this->_testModel0.load( "assets/models/apple/scene.gltf" );
		
		/*
		this->_testModel0.load( "assets/models/wooden_chair/scene.obj" );
		this->_testModel1.load( "assets/models/leather_chair/scene.obj" );
		this->_chairYellowModel.load( "assets/models/chair_yellow/scene.obj" );
		this->_toiletModel.load( "assets/models/toilet/scene.obj" ); // material 4.0
		this->_squareStoolModel.load( "assets/models/square_stool/scene.obj" );
		this->_ottomanModel.load( "assets/models/ottoman/scene.obj" );
		this->_wickerModel.load( "assets/models/chair_wicker/scene.obj" );
		this->_checkerModel.load( "assets/models/chair_checker/scene.obj" );
		this->_schoolModel.load( "assets/models/chair_school/scene.obj" );
		*/
		
		this->_woodenChair.initiate();

		//this->_testModelArray.load("assets/models/toilet/scene.obj");
		this->_testModelArray.initiate( 1000 );
		this->_testModelArray.load( "assets/models/wooden_chair/scene.obj" );
		//this->_testModelArray.load( "assets/models/wooden_crate/scene.obj" );
		//this->_testModelArray.load( "assets/models/rock/scene.obj" );


		// Skybox class
		glGenTextures( 1, &this->_cubeMapTextureId );
		glBindTexture( GL_TEXTURE_CUBE_MAP, this->_cubeMapTextureId );


		
		std::vector<std::string> textures_faces = std::vector<std::string>{
			"assets/textures/skybox/right.png",
			"assets/textures/skybox/left.png",
			"assets/textures/skybox/top.png",
			"assets/textures/skybox/bottom.png",
			"assets/textures/skybox/front.png",
			"assets/textures/skybox/back.png",
		};
	

		GLint width, height, nChannels;
		unsigned char* data;
		for ( unsigned int i = 0; i < textures_faces.size(); i++ )
		{
			data = stbi_load( textures_faces[i].c_str(), &width, &height, &nChannels, 0 );
			if ( data != nullptr )
			{

				GLenum colorMode = GL_RGB;
				switch ( nChannels )
				{
				case 1:
					colorMode = GL_RED;
					break;
				case 4:
					colorMode = GL_RGBA;
					break;
				}


				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data
				);
			}
			else
			{
				std::cout << "Cubemap failed to load at path: " << textures_faces[i] << std::endl;
			}


			stbi_image_free( data );
		}

		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );


				



		srand( glfwGetTime() ); // initialize random seed	
		float radius = 50.0;
		float offset = 2.5f;
		for ( unsigned int i = 0; i < amount; i++ )
		{
			glm::mat4 model = glm::mat4( 1.0f );
			// 1. translation: displace along circle with 'radius' in range [-offset, offset]
			float angle = ( float )i / ( float )amount * 360.0f;
			float displacement = ( rand() % ( int )( 2 * offset * 100 ) ) / 100.0f - offset;
			float x = sin( angle ) * radius + displacement;
			displacement = ( rand() % ( int )( 2 * offset * 100 ) ) / 100.0f - offset;
			float y = displacement * 0.4f; // keep height of field smaller compared to width of x and z
			displacement = ( rand() % ( int )( 2 * offset * 100 ) ) / 100.0f - offset;
			float z = cos( angle ) * radius + displacement;
			model = glm::translate( model, glm::vec3( x, y, z ) );

			// 2. scale: scale between 0.05 and 0.25f
			float scale = ( rand() % 20 ) / 100.0f + 0.05;
			model = glm::scale( model, glm::vec3( scale ) );

			// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
			float rotAngle = ( rand() % 360 );
			model = glm::rotate( model, rotAngle, glm::vec3( 0.4f, 0.6f, 0.8f ) );

			// 4. now add to list of matrices
			modelMatrices[i] = model;
		}

		return;
	}




	void update()
	{
		this->processInputs();

		return;
	}



	void render()
	{
		this->_screen.clear();


		//// Set up constant matrix projections for shaders
		glm::mat4 view = this->_camera.getViewMatrix();
		glm::mat4 projection = glm::perspective( glm::radians( this->_camera.getZoom() ), ( float )this->_screen.getWidth() / ( float )this->_screen.getHeight(), 0.1f, 2000.0f );

		this->_objectShader.use();
		this->_objectShader.setMat4( "view", view );
		this->_objectShader.setMat4( "projection", projection );


		this->_objectInstancedShader.use();
		this->_objectInstancedShader.setMat4( "view", view );
		this->_objectInstancedShader.setMat4( "projection", projection );


		this->_lightSourceShader.use();
		this->_lightSourceShader.setMat4( "view", view );
		this->_lightSourceShader.setMat4( "projection", projection );

		this->_outlineShader.use();
		this->_outlineShader.setMat4( "view", view );
		this->_outlineShader.setMat4( "projection", projection );



		glm::mat4 omniscientView = glm::mat4( glm::mat3( this->_camera.getViewMatrix() ) );
		this->_skyboxShader.use();
		this->_skyboxShader.setMat4( "view", omniscientView );
		this->_skyboxShader.setMat4( "projection", projection );





		

		//// ObjectShader

		/// Directional Light
		this->_objectShader.use();
		glm::vec4 directionalLightColor = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
		glm::vec4 directionalLightDiffuse = directionalLightColor * glm::vec4( 1.0f );
		glm::vec4 directionalLightAmbient = directionalLightDiffuse * glm::vec4( 0.025f );
		glm::vec4 directionalLightSpecular = glm::vec4( 1.0f );
		glm::vec3 directionalLightDir = glm::vec3( 0.0f, -1.0f, 1.0f );
		glm::mat4 directionalLightModel = glm::mat4( 1.0f );
		directionalLightModel = glm::translate( directionalLightModel, glm::vec3( 0.0f, 0.0f, 0.0f ) );
		glm::vec3 vDirectionalLightDirUnit = glm::normalize( glm::vec3( view * directionalLightModel * glm::vec4( glm::normalize( -directionalLightDir ), 0.0f ) ) );
		this->_objectShader.setVec3( "directionalLight.vDirection", vDirectionalLightDirUnit );
		this->_objectShader.setVec4( "directionalLight.ambient", directionalLightAmbient );
		this->_objectShader.setVec4( "directionalLight.diffuse", directionalLightDiffuse );
		this->_objectShader.setVec4( "directionalLight.specular", directionalLightSpecular );


		this->_objectInstancedShader.use();
		this->_objectInstancedShader.setVec3( "directionalLight.vDirection", vDirectionalLightDirUnit );
		this->_objectInstancedShader.setVec4( "directionalLight.ambient", directionalLightAmbient );
		this->_objectInstancedShader.setVec4( "directionalLight.diffuse", directionalLightDiffuse );
		this->_objectInstancedShader.setVec4( "directionalLight.specular", directionalLightSpecular );



		/// Point Light 0
		this->_objectShader.use();
		glm::vec4 pointLight0Color = glm::vec4( 0.5f, 0.0f, 0.5f, 1.0f );
		glm::vec4 pointLight0Diffuse = pointLight0Color * glm::vec4( 1.0f );
		glm::vec4 pointLight0Ambient = pointLight0Diffuse * glm::vec4( 0.0f );
		glm::vec4 pointLight0Specular = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
		glm::vec3 pointLight0Pos = glm::vec3( 0.0f, 15.0f, 0.0f );
		glm::vec3 vPointLight0Pos = glm::vec3( view * glm::vec4( pointLight0Pos, 1.0f ) ); // [!] model
		this->_objectShader.setVec3( "pointLights[0].vPosition", vPointLight0Pos );
		this->_objectShader.setVec4( "pointLights[0].ambient", pointLight0Ambient );
		this->_objectShader.setVec4( "pointLights[0].diffuse", pointLight0Diffuse );
		this->_objectShader.setVec4( "pointLights[0].specular", pointLight0Specular );
		this->_objectShader.setFloat( "pointLights[0].kConstant", 1.0f );
		this->_objectShader.setFloat( "pointLights[0].kLinear", 0.09f );
		this->_objectShader.setFloat( "pointLights[0].kQuadratic", 0.032f );



		this->_objectInstancedShader.use();
		this->_objectInstancedShader.setVec3( "pointLights[0].vPosition", vPointLight0Pos );
		this->_objectInstancedShader.setVec4( "pointLights[0].ambient", pointLight0Ambient );
		this->_objectInstancedShader.setVec4( "pointLights[0].diffuse", pointLight0Diffuse );
		this->_objectInstancedShader.setVec4( "pointLights[0].specular", pointLight0Specular );
		this->_objectInstancedShader.setFloat( "pointLights[0].kConstant", 1.0f );
		this->_objectInstancedShader.setFloat( "pointLights[0].kLinear", 0.09f );
		this->_objectInstancedShader.setFloat( "pointLights[0].kQuadratic", 0.032f );





		/// Spot Light 0
		glm::vec4 spotLight0Color = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f );
		glm::vec4 spotLight0Diffuse = spotLight0Color * glm::vec4( 1.0f );
		glm::vec4 spotLight0Ambient = spotLight0Diffuse * glm::vec4( 0.0f );
		glm::vec4 spotLight0Specular = glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f );
		glm::vec3 spotLight0Pos = glm::vec3( 0.0f, 0.0f, 0.0f ); // glm::vec3( 2.0f, 0.0f, 2.0f + 0.0f * std::sinf( glfwGetTime() ) );
		glm::vec3 spotLight0Dir = glm::vec3( 0.0f, 0.0f, -1.0f );
		// Position
		glm::mat4 spotLight0PosModel = glm::mat4( 1.0f );
		//spotLight0PosModel = glm::translate( spotLight0PosModel, glm::vec3( 1.5f, 0.0f, 1.5f + 0.0f * std::sinf( glfwGetTime() ) ) );
		spotLight0PosModel = glm::translate( spotLight0PosModel, spotLight0Pos );
		spotLight0PosModel = glm::rotate( spotLight0PosModel, glm::radians( 45.0f + 45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		glm::vec3 vSpotLight0Pos = glm::vec3( view * spotLight0PosModel * glm::vec4( spotLight0Pos, 1.0f ) );
		// Direction
		glm::mat4 spotLight0DirModel = glm::mat4( 1.0f );
		spotLight0DirModel = glm::rotate( spotLight0DirModel, glm::radians( 45.0f + 45.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		glm::vec3 vSpotLight0Direction = glm::vec3( view * spotLight0DirModel * glm::vec4( spotLight0Dir, 0.0f ) );
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
		


		this->_objectInstancedShader.use();
		this->_objectInstancedShader.setVec3( "spotLights[0].vPosition", vSpotLight0Pos );
		this->_objectInstancedShader.setVec3( "spotLights[0].vDirection", vSpotLight0Direction );
		this->_objectInstancedShader.setFloat( "spotLights[0].innerCutOff", glm::cos( glm::radians( 12.5f ) ) );
		this->_objectInstancedShader.setFloat( "spotLights[0].outerCutOff", glm::cos( glm::radians( 17.5f ) ) );
		this->_objectInstancedShader.setVec4( "spotLights[0].ambient", spotLight0Ambient );
		this->_objectInstancedShader.setVec4( "spotLights[0].diffuse", spotLight0Diffuse );
		this->_objectInstancedShader.setVec4( "spotLights[0].specular", spotLight0Specular );
		this->_objectInstancedShader.setFloat( "spotLights[0].kConstant", 1.0f );
		this->_objectInstancedShader.setFloat( "spotLights[0].kLinear", 0.09f );
		this->_objectInstancedShader.setFloat( "spotLights[0].kQuadratic", 0.032f );

		//// Renders before outlining (covered by outline)
		glStencilMask( 0x00 );



		
		//// Skybox
		glDepthMask( GL_FALSE );
		glCullFace( GL_FRONT );
		this->_skyboxShader.use();
		glBindTexture( GL_TEXTURE_CUBE_MAP, this->_cubeMapTextureId );
		this->_skyModel0.render( this->_skyboxShader );
		glDepthMask( GL_TRUE );
		glCullFace( GL_BACK );
		




		/*
		//// Render Floor
		this->_objectShader.use();
		glm::mat4 floorModel = glm::mat4( 1.0f );
		floorModel = glm::translate( floorModel, glm::vec3( 2.0f, -10.0f, 2.0f ) );
		floorModel = glm::scale( floorModel, glm::vec3( 50.0f, 1.0f, 50.0f ) );
		this->_objectShader.setMat4( "model", floorModel );
		glm::mat3 vNormMatrixFloor = glm::mat3( 1.0f );
		vNormMatrixFloor = glm::mat3( glm::transpose( glm::inverse( view * floorModel ) ) );
		this->_objectShader.setMat3( "vNormMatrix", vNormMatrixFloor );
		this->_objectShader.setFloat( "material.shininess", 32.0f );
		this->_testModel2.render( this->_objectShader );
		*/





		/*
		//// Renders with outlining
		// Discriminate in passing all stencil bits for the upcoming fragments, passing it's origin value by masking with 0xFF
		// Updates the stencil buffer with 1s wherever the object's fragments are rendered
		glStencilFunc( GL_ALWAYS, 1, 0xFF );
		// Enable writes to the stencil buffer
		glStencilMask( 0xFF );

		//// Render TestModel0
		this->_objectShader.use();
		glm::mat4 model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_testModel0.getPosition() );
		model = glm::rotate( model, glm::radians( 180.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
		model = glm::scale( model, this->_testModel0.getScale() );
		this->_objectShader.setMat4( "model", model );
		glm::mat3 vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_objectShader.setFloat( "material.shininess", 32.0f );
		this->_testModel0.render( this->_objectShader );








		
		//// Render outlines
		// Discriminate in passing the stencil values that do not equal 1, passing it's origin value by masking with 0xFF
		glStencilFunc( GL_NOTEQUAL, 1, 0xFF );
		// Disable stencil buffer writing
		glStencilMask( 0x00 );
		// Ignore depth test for outline to not allow the "outline effect" to discriminate other fragments in depth testings
		glDisable( GL_DEPTH_TEST );

		//// Render PointLightSourceModel Outline
		this->_outlineShader.use();
		this->_outlineShader.setMat4( "model", model );
		this->_outlineShader.setFloat( "scale", 0.1f );
		this->_outlineShader.setVec4( "color", glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f ) );
		this->_testModel0.render( this->_outlineShader );
		




		//// Renders after outlining (not covered by outline)
		



		// Return to stencil normalcy (Enable stencil buffer writing, pass through all values with no modifying, allow for depth testing)
		glStencilMask( 0xFF );
		glStencilFunc( GL_ALWAYS, 0, 0xFF );
		glEnable( GL_DEPTH_TEST );
		*/



		/*
		glm::vec3 translations[100];
		int index = 0;
		float offset = 0.1f;
		for ( int y = -10; y < 10; y += 2 )
		{
			for ( int x = -10; x < 10; x += 2 )
			{
				glm::vec3 translation;
				translation.x = ( float )x / 10.0f + offset;
				translation.y = ( float )y / 10.0f + offset;
				translation.z = 0.0f;

				translations[index++] = translation;
			}
		}
		this->_objectShader.use();
		for ( unsigned int i = 0; i < 100; i++ )
		{
			this->_objectShader.setVec3("offsets[" + std::to_string( i ) + "]", translations[i]);
		}


		//// Render Wooden Chair
		this->_objectShader.use();
		glm::mat4 model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_woodenChair.getPosition() );
		//model = glm::rotate( model, glm::radians( 0.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
		model = glm::rotate( model, glm::radians( 180.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		model = glm::scale( model, this->_woodenChair.getScale() );
		this->_objectShader.setMat4( "model", model );
		glm::mat3 vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_objectShader.setFloat( "material.shininess", 16.0f );
		this->_woodenChair.renderInstanced( this->_objectShader );
		*/






		/*
		//// Render Test Array
		this->_objectInstancedShader.use();
		glm::mat4 model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_testModelArray.getPosition() );
		model = glm::rotate( model, glm::radians( 180.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		model = glm::scale( model, this->_testModelArray.getScale() );
		this->_objectInstancedShader.setMat4( "model", model );
		glm::mat3 vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_objectInstancedShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_objectInstancedShader.setFloat( "material.shininess", 16.0f );
		this->_testModelArray.render( this->_objectInstancedShader );
		*/

		//// Render Test Array
		this->_objectInstancedShader.use();
		this->_objectInstancedShader.setFloat( "material.shininess", 16.0f );
		this->_testModelArray.render( this->_objectInstancedShader );





		/*
		//// Render TestModel1
		this->_objectShader.use();
		model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_testModel1.getPosition() );
		model = glm::rotate( model, glm::radians( 180.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );

		model = glm::scale( model, this->_testModel1.getScale() );
		this->_objectShader.setMat4( "model", model );
		vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_objectShader.setFloat( "material.shininess", 32.0f );
		this->_testModel1.render( this->_objectShader );


		//// Render Chair_Yellow
		this->_objectShader.use();
		model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_chairYellowModel.getPosition() );
		model = glm::rotate( model, glm::radians( 180.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		model = glm::scale( model, this->_chairYellowModel.getScale() );
		this->_objectShader.setMat4( "model", model );
		vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_objectShader.setFloat( "material.shininess", 0.0f );
		this->_chairYellowModel.render( this->_objectShader );



		//// Render Toilet
		this->_objectShader.use();
		model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_toiletModel.getPosition() );
		model = glm::rotate( model, glm::radians( 180.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		model = glm::scale( model, this->_toiletModel.getScale() );
		this->_objectShader.setMat4( "model", model );
		vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_objectShader.setFloat( "material.shininess", 4.0f );
		this->_toiletModel.render( this->_objectShader );



		//// Render Square Stool
		this->_objectShader.use();
		model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_squareStoolModel.getPosition() );
		model = glm::rotate( model, glm::radians( 180.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		model = glm::scale( model, this->_squareStoolModel.getScale() );
		this->_objectShader.setMat4( "model", model );
		vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_objectShader.setFloat( "material.shininess", 1024.0f );
		this->_squareStoolModel.render( this->_objectShader );
		*/

		/*
		for ( int i = 0; i < 50; i++ )
		{
			glm::vec3 randomPos = glm::vec3(
				cubeWorldPositions[i % 40].x + i / 1.0f + ( ( i % 2 == 0 ) ? 1 : -1 ) * std::cosf( glfwGetTime() * ( i / 100.0f ) ) * 5.0f * ( i / 100.0f ),
				cubeWorldPositions[i % 40].y + i / 1.0f,
				cubeWorldPositions[i % 40].z + i / 1.0f + ( ( i % 2 == 0 ) ? 1 : -1 ) * std::sinf( glfwGetTime() * ( i / 100.0f ) ) * 5.0f * ( i / 100.0f )
			);

			//// Render Ottoman
			this->_objectShader.use();
			model = glm::mat4( 1.0f );
			model = glm::translate( model, randomPos );
			model = glm::rotate( model, glm::radians( 180.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
			model = glm::scale( model, this->_ottomanModel.getScale() );
			this->_objectShader.setMat4( "model", model );
			vNormMatrix = glm::mat3( 1.0f );
			vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
			this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
			this->_objectShader.setFloat( "material.shininess", 0.0f );
			this->_ottomanModel.render( this->_objectShader );
		}

		for (int i = 0; i < 10; i++)
		{
			glm::vec3 randomPos = glm::vec3(
				cubeWorldPositions[i % 40].x + i / 1.0f + ( ( i % 2 == 0 ) ? 1 : -1 ) * std::cosf( glfwGetTime() * ( i / 100.0f ) ) * 5.0f * ( i / 100.0f ),
				cubeWorldPositions[i % 40].y + i / 1.0f,
				cubeWorldPositions[i % 40].z + i / 1.0f + ( ( i % 2 == 0 ) ? 1 : -1 ) * std::sinf( glfwGetTime() * ( i / 100.0f ) ) * 5.0f * ( i / 100.0f )
			);

			//// Render Wicker
			this->_objectShader.use();
			model = glm::mat4( 1.0f );
			model = glm::translate( model, randomPos );
			model = glm::rotate( model, glm::radians( 360.0f * (i % 2 == 0 ? 1 : -1) * std::sinf( glfwGetTime() * ( i / 100.0f ) ) ), glm::vec3( 1.0f, 0.3f, -0.4f ) );
			model = glm::scale( model, this->_wickerModel.getScale() );
			this->_objectShader.setMat4( "model", model );
			vNormMatrix = glm::mat3( 1.0f );
			vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
			this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
			this->_objectShader.setFloat( "material.shininess", 0.0f );
			this->_wickerModel.render( this->_objectShader );
		}
		*/


		/*
		//// Render Checker
		this->_objectShader.use();
		model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_checkerModel.getPosition() );
		model = glm::rotate( model, glm::radians( 180.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		model = glm::scale( model, this->_checkerModel.getScale() );
		this->_objectShader.setMat4( "model", model );
		vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_objectShader.setFloat( "material.shininess", 0.0f );
		this->_checkerModel.render( this->_objectShader );



		//// Render School
		this->_objectShader.use();
		model = glm::mat4( 1.0f );
		model = glm::translate( model, this->_schoolModel.getPosition() );
		model = glm::rotate( model, glm::radians( 180.0f * std::sinf( glfwGetTime() / 2 ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		model = glm::scale( model, this->_schoolModel.getScale() );
		this->_objectShader.setMat4( "model", model );
		vNormMatrix = glm::mat3( 1.0f );
		vNormMatrix = glm::mat3( glm::transpose( glm::inverse( view * model ) ) );
		this->_objectShader.setMat3( "vNormMatrix", vNormMatrix );
		this->_objectShader.setFloat( "material.shininess", 4.0f );
		this->_schoolModel.render( this->_objectShader );

		*/


		/*
		//// Render PointLightSourceModel
		this->_lightSourceShader.use();
		glm::vec3 pointLightSource0Pos = pointLight0Pos;
		glm::mat4 pointLightSource0Model = glm::mat4( 1.0f );
		pointLightSource0Model = glm::translate( pointLightSource0Model, pointLightSource0Pos );
		pointLightSource0Model = glm::scale( pointLightSource0Model, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", pointLightSource0Model );
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
		this->_testModel1.render( this->_lightSourceShader );
		*/









		this->_screen.newFrame();
		return;
	}

};


#endif