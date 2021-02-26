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
		Vertex vertices[] =
		{
			Vertex( glm::vec3( -0.5f,	0.5f,	0.0f ), glm::vec4( 1.0f,	0.0f,	0.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f,	-0.5f,	0.0f ), glm::vec4( 0.0f,	1.0f,	0.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,	-0.5f,	0.0f ), glm::vec4( 0.0f,	0.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,	0.5f,	0.0f ), glm::vec4( 1.0f,	1.0f,	0.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),

		};


		/*
		glm::vec4 vec( 1.0f, 0.0f, 0.0f, 1.0f );
		glm::mat4 transformer = glm::mat4( 1.0f );
		transformer = glm::translate( transformer, glm::vec3( 1.0f, 1.0f, 0.0f ) );
		vec = transformer * vec;
		std::cout << vec.x << ", " << vec.y << ", " << vec.z << std::endl;
		*/




		std::uint32_t indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};
		this->_testMesh.loadPrimitives(
			vertices, sizeof( vertices ) / sizeof( vertices[0] ), 
			indices, sizeof( indices ) / sizeof( indices[0] )
		);




		this->_texture0.load( "assets/textures/dewey_finn.jpg" );
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
		glClear( GL_COLOR_BUFFER_BIT );

		// Activate shader
		this->_shader.use();


		/*
		// Process Transform
		glm::mat4 transformer = glm::mat4( 1.0f );
		transformer = glm::translate( transformer, glm::vec3( 0.0f, 0.25f, 0.0f ) );
		transformer = glm::rotate( transformer, ( float )glfwGetTime() * 2, glm::vec3( 0.0, 0.0, 1.0 ) ); // 2) rotate around normalized z-axis
		transformer = glm::scale( transformer, glm::vec3( 0.5f, 0.5f, 0.5f ) ); // 1) scale

		this->_shader.setMat4( "transform", transformer );
		


		// Render triangle
		this->_texture0.bind( 0 );
		this->_texture1.bind( 1 );
		this->_testMesh.draw();
		*/



	


		glm::mat4 model = glm::mat4( 1.0f );
		model = glm::rotate( model, glm::radians( -55.0f ), glm::vec3( 1.0f, 0.0f, 0.0f ) );


		glm::mat4 view = glm::mat4( 1.0f );
		view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) );


		glm::mat4 projection;
		projection = glm::perspective( glm::radians( 45.0f ), 1920.0f / 1080.0f, 0.1f, 100.0f );


		this->_shader.setMat4( "model", model );
		this->_shader.setMat4( "view", view );
		this->_shader.setMat4( "projection", projection );


		// Render triangle
		this->_texture0.bind( 0 );
		this->_texture1.bind( 1 );
		this->_testMesh.draw();
	


		//this->_shader.setFloat( "xOffset", ( std::sin( glfwGetTime() * 5.0f ) / 4.0f ) );

		// Swap Buffers
		glfwSwapBuffers( this->_renderManager.getWindow() );

		return;
	}
};


#endif