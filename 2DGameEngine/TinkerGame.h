#ifndef TINKER_GAME_H
#define TINKER_GAME_H


#include <cmath>
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"

class TinkerGame : public Game
{
private:
	std::uint32_t _vao;
	Shader _shader;
	Mesh _testMesh;
public:
	TinkerGame() : Game(), _vao( 0 ), _shader(), _testMesh() {}
	TinkerGame( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) : Game( windowWidth, windowHeight, windowTitle ), _vao( 0 ), _shader(), _testMesh() {}
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
			Vertex( glm::vec3( -0.75f,	0.0f,	0.0f ), glm::vec4( 1.0f,	0.0f,	0.0f,	1.0f ) ),
			Vertex( glm::vec3( -0.5f,	0.5f,	0.0f ), glm::vec4( 0.0f,	1.0f,	0.0f,	1.0f ) ),
			Vertex( glm::vec3( -0.25f,	0.0f,	0.0f ), glm::vec4( 0.0f,	0.0f,	1.0f,	1.0f ) ),

			Vertex( glm::vec3( 0.25f,	0.0f,	0.0f ), glm::vec4( 1.0f,	0.0f,	0.0f,	1.0f ) ),
			Vertex( glm::vec3( 0.5f,	0.5f,	0.0f ), glm::vec4( 0.0f,	1.0f,	0.0f,	1.0f ) ),
			Vertex( glm::vec3( 0.75f,	0.0f,	0.0f ), glm::vec4( 0.0f,	0.0f,	1.0f,	1.0f ) ),

			Vertex( glm::vec3( -0.25f,	-0.25f,	0.0f ), glm::vec4( 1.0f,	0.0f,	0.0f,	1.0f ) ),
			Vertex( glm::vec3( 0.0f,	-0.75f,	0.0f ), glm::vec4( 0.0f,	1.0f,	0.0f,	1.0f ) ),
			Vertex( glm::vec3( 0.25f,	-0.25f,	0.0f ), glm::vec4( 0.0f,	0.0f,	1.0f,	1.0f ) )
		};

		std::uint32_t indices[] =
		{
			0, 1, 2,
			3, 4, 5,
			6, 7, 8
		};

		this->_testMesh.load( 
			vertices, sizeof( vertices ) / sizeof( vertices[0] ), 
			indices, sizeof( indices ) / sizeof( indices[0] )
		);


		return;
	}


	void update()
	{
		return;
	}


	void render()
	{
		// Clear the colorbuffer
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );

		// Activate shader
		this->_shader.use();

		// Render triangle
		this->_testMesh.draw();
		

		//glBindVertexArray( this->_vao );
		//glDrawArrays( GL_TRIANGLES, 0, 3);
		//glBindVertexArray( 0 );

		//glBindVertexArray( this->_vao );
		//glDrawElements( GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0 );

		//this->_shader.setFloat( "xOffset", ( std::sin( glfwGetTime() * 5.0f ) / 4.0f ) );

		// Swap Buffers
		glfwSwapBuffers( this->_renderManager.getWindow() );

		return;
	}
};


#endif