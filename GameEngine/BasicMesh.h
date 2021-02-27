#ifndef BASIC_MESH_H
#define BASIC_MESH_H

#include "Mesh.h"

class BasicMesh : public Mesh
{
private:

public:
	BasicMesh() : Mesh()
	{
	}


	~BasicMesh() 
	{
		if ( this->_loaded ) glDeleteVertexArrays( 1, &this->_vao );
	}


	void loadPrimitives( float* rawVertices, std::uint8_t rawVertexLength, std::size_t numRawVertices, std::uint32_t* indices, std::size_t numIndices )
	{
		this->_vertexCount = numRawVertices;
		this->_elementCount = numIndices;

		// Create and bind Vertex Array Object ( VAO )
		glGenVertexArrays( 1, &this->_vao );
		glBindVertexArray( this->_vao );

		// Create, bind Vertex Buffer Object ( VBO ) and fill with verticies data
		glGenBuffers( ( GLsizei )VBO::count, this->_vbo );
		glBindBuffer( GL_ARRAY_BUFFER, this->_vbo[( std::size_t )VBO::Position] );
		glBufferData( GL_ARRAY_BUFFER, numRawVertices * ( sizeof( rawVertices[0] ) * rawVertexLength ), rawVertices, GL_STATIC_DRAW );

		// Fill VAO with attribute pointers
		// Position attribute
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, ( sizeof( rawVertices[0] ) * rawVertexLength ), ( void* )( 0 ) );
		glEnableVertexAttribArray( 0 );
		// Normal vector attribute
		glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, ( sizeof( rawVertices[0] ) * rawVertexLength ), ( void* )( 3 * sizeof( rawVertices[0] ) ) );
		glEnableVertexAttribArray( 1 );


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

		this->_loaded = true;
		return;
	}


	void draw()
	{
		glBindVertexArray( this->_vao );
		glDrawElements( GL_TRIANGLES, this->_elementCount, GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );
		return;
	}

};

#endif // !BASIC_MESH_H
