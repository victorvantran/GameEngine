#ifndef MESH_H
#define MESH_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb/stb_image.h"
#include "Vertex.h"

class Mesh
{
private:

protected:
	enum class VBO
	{
		Position,
		count
	};

	enum class EBO
	{
		Position,
		count
	};

	GLuint _vao;
	GLuint _vbo[( std::size_t )VBO::count];
	GLuint _ebo[( std::size_t )EBO::count];
	std::uint64_t _vertexCount;
	std::uint64_t _elementCount;

	//GLuint _texture;
public:
	Mesh() : _vao( 0 ), _vbo{}, _ebo{}, _vertexCount( 0 ), _elementCount( 0 ) /*_texture( 0 )*/
	{
	}


	virtual ~Mesh() 
	{
		glDeleteVertexArrays( 1, &this->_vao );
	}


	void loadPrimitives( Vertex* vertices, std::size_t numVertices, std::uint32_t* indices, std::size_t numIndices )
	{
		this->_vertexCount = numVertices;
		this->_elementCount = numIndices;

		// Create and bind Vertex Array Object ( VAO )
		glGenVertexArrays( 1, &this->_vao );
		glBindVertexArray( this->_vao );

		// Create, bind Vertex Buffer Object ( VBO ) and fill with verticies data
		glGenBuffers( ( GLsizei )VBO::count, this->_vbo );
		glBindBuffer( GL_ARRAY_BUFFER, this->_vbo[( std::size_t )VBO::Position] );
		glBufferData( GL_ARRAY_BUFFER, numVertices * sizeof( vertices[0] ), vertices, GL_STATIC_DRAW );

		// Fill VAO with attribute pointers
		// Position attribute
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( vertices[0] ), ( void* )( 0 ) ); // Get position data // AttribPointer->layout
		glEnableVertexAttribArray( 0 );
		// Color attribute
		glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( vertices[0] ), ( void* )( 3 * sizeof( float ) ) ); // Get rgb data
		glEnableVertexAttribArray( 1 );
		// Texture coordinates attribute
		glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( vertices[0] ), ( void* )( 7 * sizeof( float ) ) ); // Get rgb data
		glEnableVertexAttribArray( 2 );

		// Bind Element Buffer Object ( EBO ) and fill with indices data
		glGenBuffers( ( GLsizei )EBO::count, this->_ebo );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_ebo[( std::size_t )EBO::Position] );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof( indices[0] ), indices, GL_STATIC_DRAW );
		
		// Unbind
		glBindVertexArray( 0 ); // Unbind VAO
		glBindBuffer( GL_ARRAY_BUFFER, 0 ); // Unbind VBO
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); // Unbind 

		// Delete Buffers after Buffer Data executed
		glDeleteBuffers( ( GLsizei )VBO::count, this->_vbo );
		glDeleteBuffers( ( GLsizei )EBO::count, this->_ebo );

		return;
	}


	/*
	void loadTexture( const char* filepath )
	{
		glGenTextures( 1, &this->_texture );
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, this->_texture );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		std::int32_t width, height, nrChannels;
		unsigned char* data = stbi_load( filepath, &width, &height, &nrChannels, 0 );
		if ( data != nullptr )
		{
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
			glGenerateMipmap( GL_TEXTURE_2D );
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}

		// Done generating texture and mipmaps, so free the image memory
		stbi_image_free( data );

		return;
	}
	*/




	void draw()
	{
		glBindVertexArray( this->_vao );
		//glBindTexture( GL_TEXTURE_2D, this->_texture );
		glDrawElements( GL_TRIANGLES, this->_elementCount, GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );
		return;
	}
};


#endif