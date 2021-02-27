#include "Mesh.h"

Mesh::Mesh() : _vao( 0 ), _vbo{}, _ebo{}, _vertexCount( 0 ), _elementCount( 0 ) /*_texture( 0 )*/
{
}


Mesh::~Mesh()
{
	glDeleteVertexArrays( 1, &this->_vao );
}


void Mesh::loadPrimitives( Vertex* vertices, std::size_t numVertices, std::uint32_t* indices, std::size_t numIndices )
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


void Mesh::draw()
{
	glBindVertexArray( this->_vao );
	glDrawElements( GL_TRIANGLES, this->_elementCount, GL_UNSIGNED_INT, 0 );
	glBindVertexArray( 0 );
	return;
}