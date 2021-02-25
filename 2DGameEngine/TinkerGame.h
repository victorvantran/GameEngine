#pragma once

#include <cmath>
#include "Game.h"
#include "Shader.h"

class TinkerGame : public Game
{
private:
	std::uint32_t _vao;
	std::uint32_t _vbo;
	std::uint32_t _ebo;

	Shader _shader;

public:
	TinkerGame() : Game() {}
	TinkerGame( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) : Game( windowWidth, windowHeight, windowTitle ) {}
	~TinkerGame() {}


	void initialize()
	{

	}


	void loadContent()
	{
		// Load shader
		this->_shader.load( "assets/shaders/vertex_core.glsl", "assets/shaders/fragment_core.glsl" );

		// Interleaved data ( x, y, r, g, b )
		float vertices[] =
		{
			-0.5f,	0.5f,	1.0f,	0.0f,	0.0f,	// top left
			0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	// top right
			-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	// bottom left
			0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	// bottom right
		};
		std::uint32_t indices[] =
		{
			0, 1, 3,
			3, 2, 0
		};


		// Create VAO and VBO and EBO
		glGenVertexArrays( 1, &this->_vao );
		glGenBuffers( 1, &this->_vbo );
		glGenBuffers( 1, &this->_ebo );
		// Bind a Vertex Array Object ( VAO )
		glBindVertexArray( this->_vao );
		// Bind Vertex Buffer Object ( VBO )
		glBindBuffer( GL_ARRAY_BUFFER, this->_vbo ); // Now any buffer calls we make ( on GL_ARRAY_BUFFER target ) will be used to configure VBO
		// Bind Element Buffer Object ( EBO )
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_ebo );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );


		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW ); // Copy the vertices data into the VBO buffer's memory
		glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), ( void* )( 0 ) ); // Get position data
		glEnableVertexAttribArray( 0 );
		glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), ( void* )( 2 * sizeof( float ) ) ); // Get rgb data
		glEnableVertexAttribArray( 1 );

		glBindBuffer( GL_ARRAY_BUFFER, 0 ); // Unbind VBO
		glBindVertexArray( 0 ); // Unbind VAO
	}


	void update()
	{

	}


	void render()
	{
		/*
		//glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClearColor( std::sin( this->_gameTime.getTotalElapsedSeconds() ), 0.0f, std::cos( this->_gameTime.getTotalElapsedSeconds() ), 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		glfwSwapBuffers( this->_renderManager.getWindow() );
		*/

		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );


		this->_shader.use();
		glBindVertexArray( this->_vao );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );


		glBindVertexArray( 0 );
		glfwSwapBuffers( this->_renderManager.getWindow() );
		return;
	}
};