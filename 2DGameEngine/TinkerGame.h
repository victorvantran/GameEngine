#ifndef TINKER_GAME_H
#define TINKER_GAME_H


#include <cmath>
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "TestMesh.h"
#include "Texture.h"

class TinkerGame : public Game
{
private:
	Shader _shader;
	TestMesh _testMesh;
	Texture _texture0;
	Texture _texture1;




	// Camera
	glm::vec3 _cameraPos = glm::vec3( 0.0f, 0.0f, 3.0f );
	glm::vec3 _cameraFront = glm::vec3( 0.0f, 0.0f, -1.0f );
	glm::vec3 _cameraUp = glm::vec3( 0.0f, 1.0f, 0.0f );


public:
	TinkerGame() : 
		Game(), 
		_shader(), 
		_testMesh(),
		_texture0(), _texture1() {}
	TinkerGame( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) :
		Game( windowWidth, windowHeight, windowTitle ), 
		_shader(), 
		_testMesh(), 
		_texture0(), _texture1() {}
	~TinkerGame() {}


	void initialize()
	{

	}


	void loadContent()
	{
		// Load Shader
		this->_shader.load( "assets/shaders/vertex_core.glsl", "assets/shaders/fragment_core.glsl" );


		// Load Mesh
		/*
		Vertex vertices[] =
		{
			Vertex( glm::vec3( -0.5f,	0.5f,	0.0f ), glm::vec4( 1.0f,	0.0f,	0.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f,	-0.5f,	0.0f ), glm::vec4( 0.0f,	1.0f,	0.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,	-0.5f,	0.0f ), glm::vec4( 0.0f,	0.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,	0.5f,	0.0f ), glm::vec4( 1.0f,	1.0f,	0.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) )
		};
		*/

		// Load Cube
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
		this->_testMesh.loadPrimitives(
			vertices, sizeof( vertices ) / sizeof( vertices[0] ), 
			indices, sizeof( indices ) / sizeof( indices[0] )
		);




		this->_texture0.load( "assets/textures/aperture_science_cube.png" );
		//this->_texture0.load( "assets/textures/dewey_finn.jpg" );
		this->_texture1.load( "assets/textures/wall.jpg" );

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




		// Activate shader
		this->_shader.use();
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




		glm::mat4 projection = glm::mat4( 1.0f );
		projection = glm::perspective( glm::radians( 45.0f ), ( float )this->_windowWidth / ( float )this->_windowHeight, 0.1f, 100.0f );

		this->_shader.setMat4( "projection", projection );

		for ( int i = 0; i < 10; i++ )
		{
			// Camera
			// Camera position
			glm::vec3 cameraPos = glm::vec3( 0.0f, 0.0f, 3.0f ); // camera position in worldSpace

			// Camera direction ( negative z-axis -> positive z-axis )
			glm::vec3 cameraTarget = glm::vec3( 0.0f, 0.0f, 0.0f ); // camera point at orign of worldSpace
			glm::vec3 cameraDirection = glm::normalize( cameraPos - cameraTarget );

			// Right axis (positive x-axis): cross product of the up vector and direction ( orthogonal )
			glm::vec3 up = glm::vec3( 0.0f, 1.0f, 0.0f );
			glm::vec3 cameraRight = glm::normalize( glm::cross( up, cameraDirection ) );

			// Up axis ( positive y-axis ): cross product of camera direction and camera right
			glm::vec3 cameraUp = glm::cross( cameraDirection, cameraRight );



			// Maniupulate camera
			const float radius = 50.0f;
			float camX = std::sinf( glfwGetTime() ) * radius;
			float camZ = std::cosf( glfwGetTime() ) * radius;
			cameraPos = glm::vec3( camX, 0.0, camZ );


			// Look At matrix (view)
			glm::mat4 view = glm::lookAt(
				cameraPos,
				cameraTarget,
				up
			);



			// Objects
			glm::mat4 model = glm::mat4( 1.0f );
			model = glm::translate( model, cubeWorldPositions[i] );
			model = glm::rotate( model, glm::radians( 360.0f * -std::sinf( i ) ), glm::vec3( 1.0f, 0.3f, -0.4f ) );
			//model = glm::translate( model, glm::vec3( 0.0f, 0.0f, -( ( 100.0f * std::sinf( glfwGetTime() ) ) + 100.0f ) / 2.0f ) );
			//model = glm::rotate( model, glm::radians( 360.0f * -std::sinf( glfwGetTime() ) ), glm::vec3( 1.0f, 0.3f, -0.4f ) );



			this->_shader.setMat4( "model", model );
			this->_shader.setMat4( "view", view );



			// Render triangle
			this->_texture0.bind( 0 );
			this->_texture1.bind( 1 );
			this->_testMesh.draw();
		}



		//this->_shader.setFloat( "xOffset", ( std::sin( glfwGetTime() * 5.0f ) / 4.0f ) );

		// Swap Buffers
		glfwSwapBuffers( this->_renderManager.getWindow() );

		return;
	}
};


#endif