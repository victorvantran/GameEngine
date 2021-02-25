#ifndef TINKER_GAME_H
#define TINKER_GAME_H


#include <cmath>
#include "Game.h"
#include "Shader.h"

class TinkerGame : public Game
{
private:
	std::uint32_t _vao;
	Shader _shader;

public:
	TinkerGame() : Game(), _vao( 0 ), _shader() {}
	TinkerGame( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) : Game( windowWidth, windowHeight, windowTitle ), _vao( 0 ), _shader() {}
	~TinkerGame() {}


	void initialize()
	{

	}


	void loadContent()
	{
		// Load shader
		this->_shader.load( "assets/shaders/vertex_core.glsl", "assets/shaders/fragment_core.glsl" );

		float vertices[] =
		{
			-0.75f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,
			-0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,
			-0.25f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,

			0.25f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	1.0f,
			0.5f,	0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	1.0f,
			0.75f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,
		};
		std::uint32_t indices[] =
		{
			0, 1, 2,
			3, 4, 5
		};

		std::uint32_t vbo, ebo;

		// Create VAO and VBO and EBO
		glGenVertexArrays( 1, &this->_vao );
		glGenBuffers( 1, &vbo );
		glGenBuffers( 1, &ebo );

		// Bind Vertex Buffer Object ( VBO ) and fill with verticies data
		glBindBuffer( GL_ARRAY_BUFFER, vbo );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW ); // Copy the vertices data into the VBO buffer's memory

		// Bind a Vertex Array Object ( VAO ) and fill with attribute pointers
		glBindVertexArray( this->_vao );
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof( float ), ( void* )( 0 ) ); // Get position data // AttribPointer->layout
		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof( float ), ( void* )( 4 * sizeof( float ) ) ); // Get rgb data
		glEnableVertexAttribArray( 1 );

		// Bind Element Buffer Object ( EBO ) and fill with indices data
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

		// Unbind
		glBindVertexArray( 0 ); // Unbind VAO
		glBindBuffer( GL_ARRAY_BUFFER, 0 ); // Unbind VBO
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); // Unbind 
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
		glBindVertexArray( this->_vao );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );


		// Unbind VAO and Swap Buffers
		glBindVertexArray( 0 );
		glfwSwapBuffers( this->_renderManager.getWindow() );

		return;
	}
};


#endif