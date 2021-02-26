#ifndef TEST_MESH_H
#define TEST_MESH_H

#include "Mesh.h"


class TestMesh : public Mesh
{
private:
	GLuint _texture0;
	GLuint _texture1;
public:
	TestMesh() : Mesh(), _texture0( 0 ), _texture1( 0 ) {}
	~TestMesh() {}
	

	void loadTextures()
	{
		stbi_set_flip_vertically_on_load(true);  

		std::int32_t width, height, nrChannels;
		unsigned char* data = nullptr;

		// Texture0
		glGenTextures( 1, &this->_texture0 );
		glBindTexture( GL_TEXTURE_2D, this->_texture0 );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		data = stbi_load( "assets/textures/dewey_finn.jpg", &width, &height, &nrChannels, STBI_rgb_alpha );
		if ( data != nullptr )
		{
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
			glGenerateMipmap( GL_TEXTURE_2D );
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}


		// Texture1
		glGenTextures( 1, &this->_texture1 );
		glBindTexture( GL_TEXTURE_2D, this->_texture1 );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		data = stbi_load( "assets/textures/stone.png", &width, &height, &nrChannels, STBI_rgb_alpha );
		if ( data != nullptr )
		{
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
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




	void draw()
	{
		// Bind texture to texture units
		glActiveTexture( GL_TEXTURE0 );
		glBindTexture( GL_TEXTURE_2D, this->_texture0 );
		glActiveTexture( GL_TEXTURE1 );
		glBindTexture( GL_TEXTURE_2D, this->_texture1 );


		glBindVertexArray( this->_vao );
		//glBindTexture( GL_TEXTURE_2D, GL_TEXTURE1 );
		//glBindTexture( GL_TEXTURE_2D, this->_texture );
		glDrawElements( GL_TRIANGLES, this->_elementCount, GL_UNSIGNED_INT, 0 );
		return;
	}
};

#endif
