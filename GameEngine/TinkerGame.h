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
	Shader _cubeShader;
	Shader _lightSourceShader;
	BasicMesh _basicMesh;
	Texture _texture0;
	Texture _texture1;




public:
	TinkerGame() : 
		Game(), 
		_cubeShader(),
		_lightSourceShader(),
		_basicMesh(),
		_texture0(), _texture1() {}
	TinkerGame( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) :
		Game( windowWidth, windowHeight, windowTitle ), 
		_cubeShader(),
		_lightSourceShader(),
		_basicMesh(),
		_texture0(), _texture1() {}
	~TinkerGame() {}


	void initialize()
	{

	}


	void loadContent()
	{
		// Load Shader
		this->_lightSourceShader.load( "assets/shaders/basic_vertex_shader.glsl", "assets/shaders/lightsource_fragment_shader.glsl" );

		
		this->_cubeShader.load( "assets/shaders/basic_vertex_shader.glsl", "assets/shaders/basic_fragment_shader.glsl" );
		this->_cubeShader.setVec3( "objectColor", glm::vec3( 1.0f, 0.5f, 0.31f ) );
		this->_cubeShader.setVec3( "lightColor", glm::vec3( 1.0f, 1.0f, 1.0f ) );



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
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
			vertices, 6,
			sizeof( vertices ) / ( sizeof( vertices[0] ) * 6 ),
			indices, sizeof( indices ) / sizeof( indices[0] )
		);




		// Load Textures
		this->_texture0.load( "assets/textures/aperture_science_cube.png" );
		this->_texture1.load( "assets/textures/wall.jpg" );
		//this->_texture0.load( "assets/textures/dewey_finn.jpg" );

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
		};

		glm::mat4 projection = glm::perspective( glm::radians( this->_camera._zoom ), ( float )this->_windowWidth / ( float )this->_windowHeight, 0.1f, 100.0f );
		glm::mat4 view = this->_camera.getViewMatrix();




		// Draw Light Source
		this->_lightSourceShader.use();
		this->_lightSourceShader.setMat4( "projection", projection );
		this->_lightSourceShader.setMat4( "view", view );
		glm::vec3 lightSourcePos = glm::vec3( 1.2f, 1.0f, 2.0f );
		glm::mat4 lightSourceModel = glm::mat4( 1.0f );
		lightSourceModel = glm::translate( lightSourceModel, lightSourcePos );
		lightSourceModel = glm::scale( lightSourceModel, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", lightSourceModel );
		this->_basicMesh.draw();


		// Draw Cube
		this->_cubeShader.use();
		this->_cubeShader.setMat4( "projection", projection );
		this->_cubeShader.setMat4( "view", view );
		this->_cubeShader.setVec3( "lightPos", lightSourcePos );
		//glm::vec3 cubePos = glm::vec3( 0.0f, 0.0f, 0.0f );
		glm::vec3 cubePos = glm::vec3( std::cosf( glfwGetTime() ) * 5.0f, 0.0f, std::sinf( glfwGetTime() ) * 5.0f );
		glm::mat4 cubeModel = glm::mat4( 1.0f );
		//cubeModel = glm::translate( cubeModel, cubePos );
		//cubeModel = glm::rotate( cubeModel, glm::radians( 360.0f * -std::sinf( glfwGetTime() ) ), glm::vec3( 1.0f, 0.3f, -0.4f ) );
		this->_cubeShader.setMat4( "model", cubeModel );

		glm::mat3 normMatrix = glm::mat3( glm::transpose( glm::inverse( cubeModel ) ) );
		this->_cubeShader.setMat3( "normMatrix", normMatrix );

		this->_cubeShader.setVec3( "viewPos", this->_camera._position );

		this->_basicMesh.draw();



		

		// Swap Buffers
		glfwSwapBuffers( this->_renderManager.getWindow() );

		return;
	}
};


#endif