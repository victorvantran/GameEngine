#include "Mesh.h"

Mesh::Mesh() : _vao( 0 ), _vbo{}, _ebo{}, _vertexCount( 0 ), _elementCount( 0 ), _loaded( false ) /*_texture( 0 )*/
{
}


Mesh::~Mesh()
{
}




void Mesh::draw()
{
	glBindVertexArray( this->_vao );
	glDrawElements( GL_TRIANGLES, this->_elementCount, GL_UNSIGNED_INT, 0 );
	glBindVertexArray( 0 );
	return;
}