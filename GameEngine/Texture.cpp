#include "Texture.h"


Texture::Texture() : _texture( 0 ) {}


Texture::Texture( const char* filepath ) : _texture( 0 ) {}


Texture::~Texture()
{
	glDeleteTextures( 1, &this->_texture );
}


void Texture::load( const char* filepath )
{
	// Load a texture image and relay data to GPU
	stbi_set_flip_vertically_on_load( true );

	std::int32_t width, height, nrChannels;
	unsigned char* imageData = nullptr;

	imageData = stbi_load( filepath, &width, &height, &nrChannels, STBI_rgb_alpha );
	if ( imageData == nullptr )
	{
		std::cout << "Failed to load texture: " << filepath << std::endl;
	}

	// Texture0
	glGenTextures( 1, &this->_texture ); // Buffer for texture
	glBindTexture( GL_TEXTURE_2D, this->_texture );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); // texture width wrap
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT ); // texture height wrap
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData ); // Send imageData to buffer
	glGenerateMipmap( GL_TEXTURE_2D );

	// Done generating texture and mipmaps, so free the image memory
	stbi_image_free( imageData );

	return;
}


void Texture::bind( std::uint8_t unit )
{
	assert( unit >= 0 && unit <= 31 );
	glActiveTexture( GL_TEXTURE0 + unit );
	glBindTexture( GL_TEXTURE_2D, this->_texture );
	return;
}
