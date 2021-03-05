#include "Mesh.h"


Mesh::Mesh( std::vector<Vertex>& vertices, std::vector<std::uint32_t>& indices, std::vector<Texture>& textures ) :
	_vertices( vertices ), _indices( indices ), _textures( textures )
{
	this->load();
}

Mesh::~Mesh()
{
}


void Mesh::cleanup()
{
	// [!] if ( set up alread condition )
	glDeleteVertexArrays( 1, &this->_vao );
	glDeleteBuffers( 1, &this->_vbo );
	glDeleteBuffers( 1, &this->_ebo );
	return;
}


void Mesh::load()
{
	glGenVertexArrays( 1, &this->_vao );
	glGenBuffers( 1, &this->_vbo );
	glGenBuffers( 1, &this->_ebo );

	/// VAO
	glBindVertexArray( this->_vao );
	
	/// VBO
	glBindBuffer( GL_ARRAY_BUFFER, this->_vbo );
	glBufferData( GL_ARRAY_BUFFER, this->_vertices.size() * sizeof( Vertex ), &this->_vertices[0], GL_STATIC_DRAW );

	/// EBO
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof( std::uint32_t ), &this->_indices[0], GL_STATIC_DRAW );


	// Position
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )0 );
	glEnableVertexAttribArray( 0 );
	// Normal
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )offsetof( Vertex, normal ) );
	glEnableVertexAttribArray( 1 );
	// TextureCoordinates
	glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, sizeof( Vertex ), ( void* )offsetof( Vertex, textureCoordinates ) );
	glEnableVertexAttribArray( 2 );


	glBindVertexArray( 0 );
	return;
}




void Mesh::render( Shader& shader )
{

	std::int8_t diffuseMapNumber = 0;
	std::int8_t specularMapNumber = 0;
	std::int8_t normalsMapNumber = 0;
	std::int8_t heightMapNumber = 0;

	for ( std::uint16_t i = 0; i < this->_textures.size(); i++ )
	{
		assert( i >= 0 && i <= 31 );
		glActiveTexture( GL_TEXTURE0 + i );


		// [!] material. struct
		std::string name;
		switch ( this->_textures[i].type )
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

		// Set the respective texture unit
		shader.setInt( name, i );
		this->_textures[i].bind();
	}

	// Render
	glBindVertexArray( this->_vao );
    glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray( 0 );

	glActiveTexture( GL_TEXTURE0 );
	return;
}


/*
void Mesh::draw( Shader& shader )
{
	std::int8_t diffuseMapNumber = 0;
	std::int8_t specularMapNumber = 0;

	for ( std::uint16_t i = 0; i < this->_textures.size(); i++ )
	{
		assert( i >= 0 && i <= 31 );
		glActiveTexture( GL_TEXTURE0 + i );
		std::string number;
		std::string type = this->_textures[i].type;

		if ( type == "texture_diffuse" )
		{
			number = std::to_string( diffuseMapNumber++ );
		}
		else if ( type == "texture_specular" )
		{
			number = std::to_string( specularMapNumber++ );
		}

		shader.setFloat( ( "material." + type + number ).c_str(), i );
		glBindTexture( GL_TEXTURE_2D, this->_textures[i].id );
	}

	glActiveTexture( GL_TEXTURE0 );


	// Render
	glBindVertexArray( this->_vao );
	glDrawElements( GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0 );
	glBindVertexArray( 0 );

	return;
}
*/