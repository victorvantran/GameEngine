#include "Texture.h"


Texture::Texture( std::string dir, std::string path, aiTextureType type ) :
	id( 0 ), directory( dir ), path( path ), type( type )
{
	this->generate();
}


Texture::~Texture()
{

}


void Texture::generate()
{
	glGenTextures( 1, &this->id );
}


void Texture::load( bool flip )
{
	stbi_set_flip_vertically_on_load( flip );

	int width, height, numChannels;

	unsigned char* data = stbi_load( (this->directory + "/" + this->path).c_str(), &width, &height, &numChannels, 0 );

	GLenum colorMode = GL_RGB;
	switch ( numChannels )
	{
	case 1:
		colorMode = GL_RED;
		break;
	case 4:
		colorMode = GL_RGBA;
		break;
	}

	if ( data != nullptr )
	{
		glBindTexture( GL_TEXTURE_2D, this->id );
		glTexImage2D( GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, data );
		glGenerateMipmap( GL_TEXTURE_2D );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}
	else
	{
		std::cout << "Image not loaded at: " << this->path << std::endl;
	}
	
	stbi_image_free( data );

	return;
}



void Texture::bind()
{
	glBindTexture( GL_TEXTURE_2D, this->id );
	return;
}



void Texture::cleanup()
{
	glDeleteTextures( 1, &this->id );
	return;
}