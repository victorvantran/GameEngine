#include "Mesh.h"


Mesh::Mesh( std::vector<Vertex>& vertices, std::vector<std::uint32_t>& indices, std::vector<Texture>& textures ) :
	_vertices( vertices ), _indices( indices ), _textures( textures )
{
	this->createVAO();
}

Mesh::~Mesh()
{
}


void Mesh::cleanup()
{
	// [!] if ( set up already condition )
	glDeleteVertexArrays( 1, &this->_vao );
	glDeleteBuffers( 1, &this->_vbo );
	glDeleteBuffers( 1, &this->_ebo );
	return;
}


void Mesh::createVAO()
{
	/// VAO
	glGenVertexArrays( 1, &this->_vao );
	glBindVertexArray( this->_vao );

	/// VBO
	glGenBuffers( 1, &this->_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, this->_vbo );
	glBufferData( GL_ARRAY_BUFFER, this->_vertices.size() * sizeof( Vertex ), &this->_vertices[0], GL_STATIC_DRAW );

	/// EBO
	glGenBuffers( 1, &this->_ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof( std::uint32_t ), &this->_indices[0], GL_STATIC_DRAW );

	/// Vertex Attribute Pointers
	// Position Attribute
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )offsetof( Vertex, position ) );
	glEnableVertexAttribArray( 0 );
	// Normal Attribute
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )offsetof( Vertex, normal ) );
	glEnableVertexAttribArray( 1 );
	// TextureCoordinates Attribute
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )offsetof( Vertex, textureCoordinates ) );
	glEnableVertexAttribArray( 2 );

	/// Clean up
	glBindVertexArray( 0 );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
	return;
}




void Mesh::render( Shader& shader )
{
	std::int8_t diffuseMapNumber = 0;
	std::int8_t specularMapNumber = 0;
	std::int8_t normalsMapNumber = 0;
	std::int8_t heightMapNumber = 0;

	for ( std::uint16_t textureUnit = 0; textureUnit < this->_textures.size(); textureUnit++ )
	{
		assert( textureUnit >= 0 && textureUnit <= 31 );

		std::string name;
		switch ( this->_textures[textureUnit].type )
		{
		case aiTextureType_DIFFUSE:
			name = "material.diffuse" + std::to_string( diffuseMapNumber++ );
			break;
		case aiTextureType_SPECULAR:
			name = "material.specular" + std::to_string( specularMapNumber++ );
			break;
		case aiTextureType_NORMALS:
			name = "material.normals" + std::to_string( normalsMapNumber++ );
			break;
		case aiTextureType_HEIGHT:
			name = "material.height" + std::to_string( heightMapNumber++ );
			break;
		}

		// Set the respective texture unit uniform
		glActiveTexture( GL_TEXTURE0 + textureUnit );
		this->_textures[textureUnit].bind();
		shader.setTextureUnit( name, textureUnit );
	}

	// Render
	glBindVertexArray( this->_vao );
    glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray( 0 );

	glActiveTexture( GL_TEXTURE0 );
	return;
}


