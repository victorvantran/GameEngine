#ifndef TINKER_GAME_H
#define TINKER_GAME_H


#include <cmath>
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "TestMesh.h"
#include "BasicMesh.h"
#include "Texture.h"

class TinkerGame : public Game
{
private:
	Shader _lightingShader;
	Shader _lightSourceShader;
	BasicMesh _basicMesh;
	Texture _diffuseTexture;
	Texture _specularTexture;
	Texture _emmisionTexture;



public:
	TinkerGame() : 
		Game(), 
		_lightingShader(),
		_lightSourceShader(),
		_basicMesh(),
		_diffuseTexture(), _specularTexture(), _emmisionTexture() {}
	TinkerGame( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) :
		Game( windowWidth, windowHeight, windowTitle ), 
		_lightingShader(),
		_lightSourceShader(),
		_basicMesh(),
		_diffuseTexture(), _specularTexture(), _emmisionTexture() {}
	~TinkerGame() {}


	void initialize()
	{

	}


	void loadContent()
	{
		// Load Textures
		//this->_diffuseTexture.load( "assets/textures/aperture_science_cube.png" );
		//this->_specularTexture.load( "assets/textures/aperture_science_cube.png" );
		//this->_diffuseTexture.load( "assets/textures/wooden_crate.png" );
		//this->_diffuseTexture.load( "assets/textures/wooden_crate_v2.jpg" );
		//this->_diffuseTexture.load( "assets/textures/brick_1.jpg" );
		this->_diffuseTexture.load( "assets/textures/white.png" );

		//this->_specularTexture.load( "assets/textures/crate_specular_borders.png" );
		//this->_specularTexture.load( "assets/textures/brick_1_specular.jpg" );
		this->_specularTexture.load( "assets/textures/white.png" );
		this->_emmisionTexture.load( "assets/textures/aperture_science_cube_emission.png" );
		


		// Load Shader
		//this->_lightSourceShader.load( "assets/shaders/basic_vertex_shader.glsl", "assets/shaders/lightsource_fragment_shader.glsl" );
		this->_lightSourceShader.load( "assets/shaders/basic_vertex_shader.glsl", "assets/shaders/lightsource_fragment_shader.glsl" );

		
		//this->_lightingShader.load( "assets/shaders/basic_vertex_shader.glsl", "assets/shaders/directional_light_fragment_shader.glsl" );
		this->_lightingShader.load( "assets/shaders/basic_vertex_shader.glsl", "assets/shaders/lighting_fragment_shader.glsl" );
		this->_lightingShader.use();
		this->_lightingShader.setInt( "material.diffuse", 0 );
		this->_lightingShader.setInt( "material.specular", 1 );
		this->_lightingShader.setInt( "material.emission", 2 );
		this->_lightingShader.setFloat( "material.shininess", 64.0f );

		// Load Meshes
		/*
		Vertex vertices[] =
		{
			Vertex( glm::vec3( -0.5f,	0.5f,	0.0f ), glm::vec4( 1.0f,	0.0f,	0.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f,	-0.5f,	0.0f ), glm::vec4( 0.0f,	1.0f,	0.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,	-0.5f,	0.0f ), glm::vec4( 0.0f,	0.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,	0.5f,	0.0f ), glm::vec4( 1.0f,	1.0f,	0.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) )
		};
		*/

		// Cube
		/*
		Vertex vertices[] =
		{
			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),

			Vertex( glm::vec3( -0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),

			Vertex( glm::vec3( -0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),

			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),

			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),

			Vertex( glm::vec3( -0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
		};


		std::uint32_t indices[] =
		{
			0, 1, 2, 3, 4, 5,
			6, 7, 8, 9, 10, 11,
			12, 13, 14, 15, 16, 17,
			18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29,
			30, 31, 32, 33, 34, 35
		};

		this->_cubeMesh.loadPrimitives(
			vertices, 6,
			sizeof( vertices ) / ( sizeof( vertices[0] * 6 ) ),
			indices, sizeof( indices ) / sizeof( indices[0] )
		);

		*/


		float vertices[] = {
			
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
		
			
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 0.0f,
			

			
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,


			
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
			 

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 1.0f,


			
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 1.0f
			

		};

		std::uint32_t indices[] =
		{
			0, 1, 2, 3, 4, 5,
			6, 7, 8, 9, 10, 11,
			12, 13, 14, 15, 16, 17,
			18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29,
			30, 31, 32, 33, 34, 35
		};

		this->_basicMesh.loadPrimitives(
			vertices, 8,
			sizeof( vertices ) / ( sizeof( vertices[0] ) * 8 ),
			indices, sizeof( indices ) / sizeof( indices[0] )
		);




		return;
	}


	void update()
	{
		this->processInput( this->_renderManager.getWindow() );

		return;
	}


	void render()
	{
		// Clear the colorbuffer
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// World Environment
		/*
		glm::vec3 cubeWorldPositions[] =
		{
			glm::vec3( 0.0f,  0.0f,  0.0f ),
			glm::vec3( 2.0f,  5.0f, -5.0f ),
			glm::vec3( -1.5f, -2.2f, -2.5f ),
			glm::vec3( -3.8f, -2.0f, -12.3f ),
			glm::vec3( 2.4f, -0.4f, -3.5f ),
			glm::vec3( -1.7f,  3.0f, -7.5f ),
			glm::vec3( 1.3f, -2.0f, -2.5f ),
			glm::vec3( 1.5f,  2.0f, -2.5f ),
			glm::vec3( 1.5f,  0.2f, -1.5f ),
			glm::vec3( -1.3f,  1.0f, -1.5f )
		};*/
		glm::vec3 cubeWorldPositions[] =
		{
			glm::vec3( 0.0f,  0.0f,  0.0f ),
			glm::vec3( 2.0f,  5.0f, -5.0f ),
			glm::vec3( -1.5f, -2.2f, -2.5f ),
			glm::vec3( -3.8f, -2.0f, -12.3f ),
			glm::vec3( 2.4f, -0.4f, -3.5f ),
			glm::vec3( -1.7f,  3.0f, -7.5f ),
			glm::vec3( 1.3f, -2.0f, -2.5f ),
			glm::vec3( 1.5f,  2.0f, -2.5f ),
			glm::vec3( 1.5f,  0.2f, -1.5f ),
			glm::vec3( -1.3f,  1.0f, -1.5f ),

			glm::vec3( 10.0f,  20.0f,  10.0f ),
			glm::vec3( 12.0f,  15.0f, -51.0f ),
			glm::vec3( -11.5f, -12.2f, -2.5f ),
			glm::vec3( -31.8f, -2.0f, -12.3f ),
			glm::vec3( 21.4f, -10.4f, -3.5f ),
			glm::vec3( -11.7f,  31.0f, -7.5f ),
			glm::vec3( 11.3f, -2.0f, -2.5f ),
			glm::vec3( 11.5f,  2.0f, -12.5f ),
			glm::vec3( 11.5f,  10.2f, -11.5f ),
			glm::vec3( -1.3f,  1.0f, -11.5f ),



			glm::vec3( 20.0f,  20.0f,  20.0f ),
			glm::vec3( 12.0f,  25.0f, -21.0f ),
			glm::vec3( -21.5f, -12.2f, -22.5f ),
			glm::vec3( -21.8f, -22.0f, -12.3f ),
			glm::vec3( 22.4f, -12.4f, -23.5f ),
			glm::vec3( -12.7f,  31.0f, -7.5f ),
			glm::vec3( 11.3f, -22.0f, -2.5f ),
			glm::vec3( 21.5f,  2.0f, -22.5f ),
			glm::vec3( 21.5f,  20.2f, -11.5f ),
			glm::vec3( -2.3f,  1.0f, -21.5f ),



			glm::vec3( 30.0f,  23.0f,  23.0f ),
			glm::vec3( 12.0f,  25.0f, -31.0f ),
			glm::vec3( -23.5f, -13.2f, -32.5f ),
			glm::vec3( -31.8f, -22.0f, -12.3f ),
			glm::vec3( 22.3f, -32.4f, -23.5f ),
			glm::vec3( -12.7f,  33.0f, -37.5f ),
			glm::vec3( 13.3f, -22.0f, -32.5f ),
			glm::vec3( 23.5f,  2.0f, -22.5f ),
			glm::vec3( 31.5f,  20.2f, -11.5f ),
			glm::vec3( -2.3f,  1.0f, -31.5f ),



			glm::vec3( 40.0f,  24.0f,  23.0f ),
			glm::vec3( 12.0f,  24.0f, -41.0f ),
			glm::vec3( -23.5f, -43.2f, -32.5f ),
			glm::vec3( -34.8f, -42.0f, -12.3f ),
			glm::vec3( 22.4f, -42.4f, -23.5f ),
			glm::vec3( -12.7f,  43.0f, -34.5f ),
			glm::vec3( 14.3f, -22.0f, -34.5f ),
			glm::vec3( 43.5f,  2.0f, -22.5f ),
			glm::vec3( 41.5f,  40.2f, -11.5f ),
			glm::vec3( -4.3f,  4.0f, -31.5f ),
		};



		glm::mat4 projection = glm::perspective( glm::radians( this->_camera._zoom ), ( float )this->_windowWidth / ( float )this->_windowHeight, 0.1f, 2000.0f );
		glm::mat4 view = this->_camera.getViewMatrix();

		this->_lightSourceShader.use();
		this->_lightSourceShader.setMat4( "projection", projection );
		this->_lightSourceShader.setMat4( "view", view );

		this->_lightingShader.use();
		this->_lightingShader.setMat4( "projection", projection );
		this->_lightingShader.setMat4( "view", view );





		/// Directional Light
		this->_lightingShader.use();
		glm::vec3 directionalLightColor = glm::vec3( 0.0f, 0.0f, 1.0f );
		glm::vec3 directionalLightDiffuse = directionalLightColor * glm::vec3( 1.0f );
		glm::vec3 directionalLightAmbient = directionalLightDiffuse * glm::vec3( 0.0f );
		glm::vec3 directionalLightPos = glm::vec3( 0.0f, 0.0f, -1000.0f );


		glm::mat4 directionalLightModel = glm::mat4( 1.0f );
		directionalLightModel = glm::translate( directionalLightModel, glm::vec3( 0.0f, 0.0f, 0.0f ) );
		//glm::vec3 vDirectionalLightPos = glm::vec3( view * directionalLightModel * glm::vec4( directionalLightPos, 1.0f ) );
		glm::vec3 vDirectionalLightPos = directionalLightPos;



		//this->_lightingShader.setVec3( "directionalLight.vDirection", glm::vec3( view * glm::vec4( directionalLightPos, 1.0f ) ) );
		this->_lightingShader.setVec3( "directionalLight.vDirection", vDirectionalLightPos );

		this->_lightingShader.setVec3( "directionalLight.ambient", directionalLightAmbient );
		this->_lightingShader.setVec3( "directionalLight.diffuse", directionalLightDiffuse );
		this->_lightingShader.setVec3( "directionalLight.specular", glm::vec3( 1.0f ) );




		/// Point Light 0
		this->_lightingShader.use();
		glm::vec3 pointLight0Color = glm::vec3( 1.0f, 0.0f, 0.0f );
		glm::vec3 pointLight0Diffuse = pointLight0Color * glm::vec3( 0.8f );
		glm::vec3 pointLight0Ambient = pointLight0Diffuse * glm::vec3( 0.0f );
		glm::vec3 pointLight0Pos = glm::vec3( 1.2f, 1.0f, 2.0f );
		glm::vec3 vPointLight0Pos = glm::vec3( view * glm::vec4( pointLight0Pos, 1.0f ) );
		this->_lightingShader.setVec3( "pointLights[0].vPosition", vPointLight0Pos );
		this->_lightingShader.setVec3( "pointLights[0].ambient", pointLight0Ambient );
		this->_lightingShader.setVec3( "pointLights[0].diffuse", pointLight0Diffuse );
		this->_lightingShader.setVec3( "pointLights[0].specular", glm::vec3( 1.0f ) );
		this->_lightingShader.setFloat( "pointLights[0].kConstant", 1.0f );
		this->_lightingShader.setFloat( "pointLights[0].kLinear", 0.09f );
		this->_lightingShader.setFloat( "pointLights[0].kQuadratic", 0.032f );



		/// Point Light 1
		this->_lightingShader.use();
		glm::vec3 pointLight1Color = glm::vec3( 0.0f, 1.0f, 0.0f );
		glm::vec3 pointLight1Diffuse = pointLight1Color * glm::vec3( 0.8f );
		glm::vec3 pointLight1Ambient = pointLight1Diffuse * glm::vec3( 0.0f );
		glm::vec3 pointLight1Pos = glm::vec3( 7.2f, 7.0f, 7.0f );
		glm::vec3 vPointLight1Pos = glm::vec3( view * glm::vec4( pointLight1Pos, 1.0f ) );
		this->_lightingShader.setVec3( "pointLights[1].vPosition", vPointLight1Pos );
		this->_lightingShader.setVec3( "pointLights[1].ambient", pointLight1Ambient );
		this->_lightingShader.setVec3( "pointLights[1].diffuse", pointLight1Diffuse );
		this->_lightingShader.setVec3( "pointLights[1].specular", glm::vec3( 1.0f ) );
		this->_lightingShader.setFloat( "pointLights[1].kConstant", 1.0f );
		this->_lightingShader.setFloat( "pointLights[1].kLinear", 0.09f );
		this->_lightingShader.setFloat( "pointLights[1].kQuadratic", 0.032f );


		

		/// Spot Light 0
		glm::vec3 spotLight0Color = glm::vec3( 1.0f, 1.0f, 0.0f );
		glm::vec3 spotLight0Diffuse = spotLight0Color * glm::vec3( 1.0f );
		glm::vec3 spotLight0Ambient = spotLight0Diffuse * glm::vec3( 0.0f );
		glm::vec3 lSpotLight0Pos = glm::vec3( 0.0f, 0.0f, 0.0f );
		glm::vec3 lSpotLight0Dir = glm::vec3( 0.0f, 0.0f, 1.0f );
		// Position
		glm::mat4 spotLight0PosModel = glm::mat4( 1.0f );
		spotLight0PosModel = glm::translate( spotLight0PosModel, glm::vec3( 0.0f, 30.0f, 0.0f ) );
		spotLight0PosModel = glm::rotate( spotLight0PosModel, glm::radians( 180.0f * std::sinf( glfwGetTime() ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		glm::vec3 wSpotLight0Pos = glm::vec3( spotLight0PosModel * glm::vec4( lSpotLight0Pos, 1.0f ) );
		glm::vec3 vSpotLight0Pos = glm::vec3( view * spotLight0PosModel * glm::vec4( lSpotLight0Pos, 1.0f ) );
		// Direction
		glm::mat4 spotLight0DirModel = glm::mat4( 1.0f );
		spotLight0DirModel = glm::rotate( spotLight0DirModel, glm::radians( 180.0f * std::sinf( glfwGetTime() ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		glm::vec3 wSpotLight0Direction = glm::vec3( spotLight0DirModel * glm::vec4( lSpotLight0Dir, 1.0f ) );
		// Set uniform
		this->_lightingShader.setVec3( "spotLights[0].wPosition", wSpotLight0Pos );
		this->_lightingShader.setVec3( "spotLights[0].vPosition", vSpotLight0Pos );
		this->_lightingShader.setVec3( "spotLights[0].wDirection", wSpotLight0Direction );
		this->_lightingShader.setFloat( "spotLights[0].innerCutOff", glm::cos( glm::radians( 12.5f ) ) );
		this->_lightingShader.setFloat( "spotLights[0].outerCutOff", glm::cos( glm::radians( 12.5f ) ) );
		this->_lightingShader.setVec3( "spotLights[0].ambient", spotLight0Ambient );
		this->_lightingShader.setVec3( "spotLights[0].diffuse", spotLight0Diffuse );
		this->_lightingShader.setVec3( "spotLights[0].specular", glm::vec3( 1.0f ) );
		this->_lightingShader.setFloat( "spotLights[0].kConstant", 1.0f );
		this->_lightingShader.setFloat( "spotLights[0].kLinear", 0.09f );
		this->_lightingShader.setFloat( "spotLights[0].kQuadratic", 0.032f );






		
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
		this->_lightingShader.setVec3( "spotLights[1].wPosition", wSpotLight1Pos );
		this->_lightingShader.setVec3( "spotLights[1].vPosition", vSpotLight1Pos );
		this->_lightingShader.setVec3( "spotLights[1].wDirection", wSpotLight1Direction );
		this->_lightingShader.setFloat( "spotLights[1].innerCutOff", glm::cos( glm::radians( 12.5f ) ) );
		this->_lightingShader.setFloat( "spotLights[1].outerCutOff", glm::cos( glm::radians( 12.5f ) ) );
		this->_lightingShader.setVec3( "spotLights[1].ambient", spotLight1Ambient );
		this->_lightingShader.setVec3( "spotLights[1].diffuse", spotLight1Diffuse );
		this->_lightingShader.setVec3( "spotLights[1].specular", glm::vec3( 1.0f ) );
		this->_lightingShader.setFloat( "spotLights[1].kConstant", 1.0f );
		this->_lightingShader.setFloat( "spotLights[1].kLinear", 0.09f );
		this->_lightingShader.setFloat( "spotLights[1].kQuadratic", 0.032f );

	






		
		/// PointLight0 Source
		this->_lightSourceShader.use();
		glm::mat4 pointLight0Model = glm::mat4( 1.0f );
		pointLight0Model = glm::translate( pointLight0Model, pointLight0Pos );
		pointLight0Model = glm::scale( pointLight0Model, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", pointLight0Model );
		this->_lightSourceShader.setVec3( "lightColor", pointLight0Color );
		this->_basicMesh.draw();


		/// PointLight1 Source
		this->_lightSourceShader.use();
		glm::mat4 pointLight1Model = glm::mat4( 1.0f );
		pointLight1Model = glm::translate( pointLight1Model, pointLight1Pos );
		pointLight1Model = glm::scale( pointLight1Model, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", pointLight1Model );
		this->_lightSourceShader.setVec3( "lightColor", pointLight1Color );
		this->_basicMesh.draw();
		

		/// SpotLight0 Source
		this->_lightSourceShader.use();
		glm::mat4 spotLightSource0Model = glm::mat4( 1.0f );
		spotLightSource0Model = glm::translate( spotLightSource0Model, glm::vec3( 0.0f, 30.0f, 0.0f ) );
		spotLightSource0Model = glm::rotate( spotLightSource0Model, glm::radians( 180.0f * std::sinf( glfwGetTime() ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		spotLightSource0Model = glm::scale( spotLightSource0Model, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", spotLightSource0Model );
		this->_lightSourceShader.setVec3( "lightColor", spotLight0Color );
		this->_basicMesh.draw();


		/// SpotLight1 Source
		this->_lightSourceShader.use();
		glm::mat4 spotLightSource1Model = glm::mat4( 1.0f );
		spotLightSource1Model = glm::translate( spotLightSource1Model, glm::vec3( 0.0f, -10.0f, 0.0f ) );
		spotLightSource1Model = glm::rotate( spotLightSource1Model, glm::radians( 180.0f * -std::sinf( glfwGetTime() ) ), glm::vec3( 0.0f, 1.0f, 0.0f ) );
		spotLightSource1Model = glm::scale( spotLightSource1Model, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", spotLightSource1Model );
		this->_lightSourceShader.setVec3( "lightColor", spotLight1Color );
		this->_basicMesh.draw();














		this->_diffuseTexture.bind( 0 );
		this->_specularTexture.bind( 1 );
		//this->_emmisionTexture.bind( 0 );


		// Wall
		this->_lightingShader.use();
		glm::vec3 cube1Pos = glm::vec3( 0.0f, 0.0f, 10.0f );
		glm::mat4 cube1Model = glm::mat4( 1.0f );
		cube1Model = glm::translate( cube1Model, cube1Pos );
		cube1Model = glm::scale( cube1Model, glm::vec3( 100.0f, 100.0f, 1.0f ) );
		this->_lightingShader.setMat4( "model", cube1Model );
		glm::mat3 normMatrix1 = glm::mat3( glm::transpose( glm::inverse( view * cube1Model ) ) );
		normMatrix1 = glm::mat3( glm::transpose( glm::inverse( view * cube1Model ) ) );
		this->_lightingShader.setMat3( "normMatrix", normMatrix1 );
		this->_basicMesh.draw();


		this->_lightingShader.use();
		glm::vec3 cube2Pos = glm::vec3( 0.0f, 0.0f, -30.0f );
		glm::mat4 cube2Model = glm::mat4( 1.0f );
		cube2Model = glm::translate( cube2Model, cube2Pos );
		cube2Model = glm::scale( cube2Model, glm::vec3( 100.0f, 100.0f, 1.0f ) );
		this->_lightingShader.setMat4( "model", cube2Model );
		glm::mat3 normMatrix2 = glm::mat3( glm::transpose( glm::inverse( view * cube2Model ) ) );
		normMatrix2 = glm::mat3( glm::transpose( glm::inverse( view * cube2Model ) ) );
		this->_lightingShader.setMat3( "normMatrix", normMatrix2 );
		this->_basicMesh.draw();


		// Cubes
		this->_lightingShader.use();
		glm::vec3 cube0Pos = glm::vec3( 0.0f, 0.0f, 0.0f );
		glm::mat4 cube0Model = glm::mat4( 1.0f );
		cube0Model = glm::translate( cube0Model, cube0Pos );
		cube0Model = glm::scale( cube0Model, glm::vec3( 1.0f, 1.0f, 1.0f ) );
		this->_lightingShader.setMat4( "model", cube0Model );
		glm::mat3 normMatrix0 = glm::mat3( glm::transpose( glm::inverse( view * cube0Model ) ) );
		this->_lightingShader.setMat3( "normMatrix", normMatrix0 );
		this->_basicMesh.draw();


		// Draw Cubes
		/*
		for ( int i = 0; i < 2000; i++ )
		{
			this->_lightingShader.use();

			// World Properties
			//glm::vec3 cubePos = glm::vec3( 0.0f, 0.0f, 0.0f );
			glm::vec3 cubePos = glm::vec3(
				cubeWorldPositions[i % 40].x + i / 10.0f + ( ( i % 2 == 0 ) ? 1 : -1 ) * std::cosf( glfwGetTime() * ( i / 1000.0f ) ) * 5.0f * ( i / 1000.0f ),
				cubeWorldPositions[i % 40].y + i / 10.0f,
				cubeWorldPositions[i % 40].z + i / 10.0f + ( ( i % 2 == 0 ) ? 1 : -1 ) * std::sinf( glfwGetTime() * ( i / 1000.0f ) ) * 5.0f * ( i / 1000.0f )
			);
			glm::mat4 cubeModel = glm::mat4( 1.0f );
			cubeModel = glm::translate( cubeModel, cubePos );
			cubeModel = glm::rotate( cubeModel, glm::radians( 360.0f * -std::sinf( glfwGetTime() * ( i / 1000.0f ) ) ), glm::vec3( 1.0f, 0.3f, -0.4f ) );
			this->_lightingShader.setMat4( "model", cubeModel );


			// Prepare lighting in view coordinates
			glm::mat3 normMatrix = glm::mat3( glm::transpose( glm::inverse( view * cubeModel ) ) );
			this->_lightingShader.setMat3( "normMatrix", normMatrix );


			// Bind texture
			this->_diffuseTexture.bind( 0 );
			this->_specularTexture.bind( 1 );
			//this->_emmisionTexture.bind( 2 );

			// Draw
			this->_basicMesh.draw();
		}
		*/



		// Swap Buffers
		glfwSwapBuffers( this->_renderManager.getWindow() );

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