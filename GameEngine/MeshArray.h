#ifndef MESH_ARRAY_H
#define MESH_ARRAY_H



#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>

#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"


class MeshArray
{
private:
	std::vector<Vertex>			_vertices;
	std::vector<std::uint32_t>	_indices;
	std::vector<Texture>		_textures;
	std::vector<glm::vec3>& _instances; // for now instances is defined by world position


private:
	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;
	GLuint _instanceVBO;

	void createVAO()
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


		std::cout << "Instances: " << this->_instances.size() << std::endl;
		std::cout << "Instance: " << this->_instances[0].x << ", " << this->_instances[0].y << ", " << this->_instances[0].z << std::endl;

	
		

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


		/// Instance VBO
		glGenBuffers( 1, &this->_instanceVBO );
		glBindBuffer( GL_ARRAY_BUFFER, this->_instanceVBO );
		glBufferData( GL_ARRAY_BUFFER, this->_instances.size() * sizeof( glm::vec3 ), &this->_instances[0], GL_STATIC_DRAW );
		
		// Instance Id Attribute
		glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, sizeof( glm::vec3 ), ( void* )0 );
		glEnableVertexAttribArray( 3 );
		glVertexAttribDivisor( 3, 1 );
		



		/// Clean up
		glBindVertexArray( 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		return;
	}



public:
	MeshArray( std::vector<Vertex>& vertices, std::vector<std::uint32_t>& indices, std::vector<Texture>& textures, std::vector<glm::vec3>& instances )
		: _vertices( vertices ), _indices( indices ), _textures( textures ), _instances(instances)
	{
		this->createVAO();
	}


	~MeshArray()
	{
	}



	void render( Shader& shader )
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
		//std::cout << "Instance: " << this->_instances[0].x << ", " << this->_instances[0].y << ", " << this->_instances[0].z << std::endl;
		glBindVertexArray( this->_vao );
		glDrawElementsInstanced( GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0, this->_instances.size() );
		//glDrawElements( GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0 );
		glBindVertexArray( 0 );

		glActiveTexture( GL_TEXTURE0 );
		return;
	}


	void cleanup()
	{
		glDeleteVertexArrays( 1, &this->_vao );
		glDeleteBuffers( 1, &this->_vbo );
		glDeleteBuffers( 1, &this->_ebo );
		glDeleteBuffers( 1, &this->_instanceVBO );
	}
};



#endif